/*
 * TimPrinter.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: borja
 */

#include "TimPrinter.h"

TimPrinter::TimPrinter() {
	// TODO Auto-generated constructor stub
	this->listener=false;
	this->temp =0;
}



TimPrinter::~TimPrinter() {
	// TODO Auto-generated destructor stub
}

string TimPrinter::partialHex(int dec, int base) {
	string numeroHex = "";
	stringstream stream;
	if (dec < base) {
		switch (dec) {
		case 10:
			numeroHex = "A";
			break;
		case 11:
			numeroHex = "B";
			break;
		case 12:
			numeroHex = "C";
			break;
		case 13:
			numeroHex = "D";
			break;
		case 14:
			numeroHex = "E";
			break;
		case 15:
			numeroHex = "F";
			break;
		default:
			stream << dec;
			numeroHex = stream.str();
			break;
		}
		return numeroHex;
	}
	return "error";
}

string TimPrinter::HexToStr(int dec, int base) {
	int cociente = 16, residuo = 0;
	string numeroHex = "", numeroHex1 = "";

	while (dec >= base) {
		cociente = dec / base;
		residuo = dec % base;
		dec = cociente;
		numeroHex1 = partialHex(residuo,base);
		numeroHex = numeroHex1 + numeroHex;
		dec = cociente;
	}
	numeroHex1 = partialHex(dec,base);
	numeroHex = numeroHex1 + numeroHex;
	if (numeroHex.length() == 1)
		numeroHex = "0" + numeroHex;
	return numeroHex;
}

int TimPrinter::StrToInt(string id) {
	if (id[0] > '9')
		id[0] -= 7;
	if (id[1] > '9')
		id[1] -= 7;
	return ((id[0] - 48) * 16) + (id[1] - 48);
}


void TimPrinter::Open(string port){
	this->conector.Open_Port(port);
	this->conector.Configure_Port(B9600,"8N1"); 
}
	
void TimPrinter::Close(){
	this->conector.Close_Port();
}
string TimPrinter::calculateCRC(string command) {
	int size = command.size(), amount = 0;
	string out;
	for (int i = 0; i < size; i++) {
		amount = amount ^ (int) command[i];
	}
	//amount = amount % 256;
	out  = (char)amount;
	return out;
}

bool TimPrinter::checkCRC(string msg){
	string crc, msgCRC = msg.substr(msg.length()-3,2);
	crc = msg.substr(1,msg.length()-4);
	crc = this->calculateCRC(crc);
	return(crc == msgCRC);
}

bool TimPrinter::sendMessage(string msg){
	string msg_str = (string)"\x16"+(string)"\x16"+(string)"\x16"+(string)"\x02";
	string	crc = calculateCRC(msg+'\x03');

	msg_str += msg+(string)"\x03"+crc;
	conector.Write_Port(msg_str);
	push_Debug("Enviamos "+msg_str);
	return true;
}

void TimPrinter::writeCard(string source,string encode, string text){
	string block = ExCode,number,codeBlock,textBlock,segment;
//	Ex1 S? D9 T2 R? W1 P2
	block += source+DstCode+Track+(string)"1";

	if (encode !=""){
		block +=WrCode;			number = (char)(encode.size()+ 0x20);
		codeBlock= (string)"4"+Track+number+encode;
	}
	else	block +="0";
	if (text != ""){
		block +=PrintCode;		number = (char)(text.size()+ 0x20);
		textBlock="6"+number+text;
	}
	else	block +="0";

	block += codeBlock+textBlock;
	this->sendMessage(block);
	//this->sendMessage("0000");
	this->sendMessage("0001");
	//this->sendMessage("0002");
}

void TimPrinter::ejectCard(){
	string block="";
	//	Ex1 S? D9 T2 R? W1 P2
		block += ExCode+AnyWhere+DstCode+Track+(string)"0"+(string)"0"+(string)"0";
		this->sendMessage(block);
}

void TimPrinter::runListener(){
	string input;
	char car;
	while(this->listener){
		if (this->conector.WaitForBlock() != 0){
		//	this->conector.Gets_Port(input);
		//	push_Debug("runListener:: "+input);
			this->conector.Getc_Port(&car);
			cout << car<< endl;
			input ="";
		}
	}
}

void *TimPrinter::Handle_Thread(void *thread) {
	((TimPrinter *) thread)->runListener();
	return NULL;
}

void TimPrinter::launchListener(){
	if (!this->listener){
		this->listener=true;
		pthread_create(new pthread_t, NULL, &TimPrinter::Handle_Thread,  (void *)this);
	}
}

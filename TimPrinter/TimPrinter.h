/*
 * conectorBusCan.h
 *
 *  Created on: Aug 20, 2013
 *      Author: borja
 */

#ifndef TIMPRINTER_H_
#define TIMPRINTER_H_

#include <map>
#include <iostream>
#include <string>
#include <list>
#include <set>

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>  

using namespace std;

#include "conectorSerial.h"
#include "../configuration/configuration.h"
#define ENABLE_SERIAL_PORT_EVENT

enum CtrSymbMessage{
	SYN=0x16,
	STX=0x02,
	ETX=0x03
};

enum Origincode{
	org_C4=0x30,
	org_C1=0x31,
	org_STOCK=0x33,
	org_PARKING=0x34,
	org_FRONT=0x36,
	org_locate_pos=0x38
};

enum DestCode{
	dest_C4=0x30,
	dest_C1=0x31,
	dest_PARKING=0x34,
	dest_REJECT=0x35,
	dest_IC=0x37,
	dest_EXIT=0x39
};

enum TrackCode{
	NoTrack=0x30,
	Track1,
	Track2,
	Track1_2,
	Track3,
	Track1_3,
	Track2_3,
	Track1_2_3
};

class TimPrinter {
private:
	
protected: // atributos
	conectorSerial conector;
	bool listener;
	int temp;

protected: // Ejecución de comandos.


	string partialHex(int dec, int base=16);
	string HexToStr(int dec, int base=16);

	int StrToInt(string id);
	bool checkCRC(string msg);	
	
	string calculateCRC(string command);
	string StrToDbHex(string text);
	
	void runListener();

		static void *Handle_Thread(void *thread);

public:
	//typedef struct
	TimPrinter();
	virtual ~TimPrinter();
	
	bool sendMessage(string msg);
	

	void writeCard(string encode, string text);
	void Open(string port="/dev/ttyUSB0");
	
	void launchListener();

	void Close();
};

#endif /* TIMPRINTER_H_ */

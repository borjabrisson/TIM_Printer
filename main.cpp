#include "serverIP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "configuration/configuration.h"

#include <sys/types.h> 

#include "TimPrinter/conectorSerial.h"
#include "TimPrinter/TimPrinter.h"

#include <iostream>

#include <map>
#include <iostream>
#include <string>
#include <list>
#include <set>
using namespace std;
#define ENABLE_SERIAL_PORT_EVENT

TimPrinter conector;

int main(int argc, char *argv[]) {
	//apiBusCan conector;
	//serverIP server;
	string cmd, node, args;

	//conector.Open();
	string input;
	conector.Open("/dev/ttyS0");
	//conector.Open();

	//pruebaCMDList();
	//pruebaAlarma();
	conector.launchListener();
	//conector.sendMessage("169301151&ABCEDF2(012345676/ML ELECTRONIQUE");
	//conector.sendMessage("139201242&1234566)PRUEBAS 2");

	//cout << "CRC: "<< conector.calculateCRC("139201242&1234566)PRUEBAS 2\x03")<< endl;



	conector.writeCard("6","","        23");
	//conector.ejectCard();
	cin >> input;

	conector.Close(); // Cierro el puerto serie.
	printf("\nHasta la proxima\n");
	return 0;
}

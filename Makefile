CC := g++ -std=c++03
BASEFLAGS=  -lpthread 
CPPFLAGS = -O0 -g3 -Wall -c -fmessage-length=0  -MMD -MP
MySQLFLAGS = `mysql_config --cflags --libs`

all	: TimPrinter
#listen serverIP
	#${CC} main.cpp -o tim.out "serie.o"  "TimPrinter.o" "requestHandler.o" "serverIP.o" -fpermissive ${BASEFLAGS}
	${CC} main.cpp -o tim.out "serie.o"  "TimPrinter.o" -fpermissive ${BASEFLAGS}  
	rm *.o *.d
serverIP: listen
	${CC} -fpermissive ${BASEFLAGS}  ${CPPFLAGS} -MF"serverIP.d" -MT"serverIP.d" -o "serverIP.o" serverIP.cpp
listen	: TimPrinter
	${CC} ${BASEFLAGS} ${CPPFLAGS} -MF"requestHandler.d" -MT"requestHandler.d" -o "requestHandler.o" listen/requestHandler.cpp
conectorSerial	: 
	${CC} -fpermissive ${BASEFLAGS} ${CPPFLAGS} -MF"serie.d" -MT"serie.d" -o "serie.o" TimPrinter/conectorSerial.cpp
TimPrinter : conectorSerial
	${CC} -fpermissive ${BASEFLAGS} ${CPPFLAGS} -MF"TimPrinter.d" -MT"TimPrinter.d" -o "TimPrinter.o"  TimPrinter/TimPrinter.cpp
clean	:
	rm *.o *.d
no-temporal:
	rm *.cpp~ *.h~ */*.cpp~ */*.h~


CC = g++ -Wall -W -Wextra -std=c++11
LIBS = -pthread

# clean
clean:
	rm *.out *.o

# client modules
ClientTest: ClientTest.o Client.o Session.o
	$(CC) $(LIBS) -o ./ClientTest.out ClientTest.o Client.o Session.o

Client.o: Client.cpp Client.h
	$(CC) -c Client.cpp

# server modules
ServerTest: ServerTest.o Server.o Session.o ReceiveProcess.o
	$(CC) $(LIBS) -o ./ServerTest.out ServerTest.o Server.o Session.o ReceiveProcess.o

Server.o: Server.cpp Server.h
	$(CC) -c Server.cpp

ReceiveProcess.o: ReceiveProcess.cpp ReceiveProcess.h
	$(CC) -c ReceiveProcess.cpp

# shared helper modules
Session.o: Session.cpp Session.h
	$(CC) -c Session.cpp


CC = g++ -Wall -W -Wextra -std=c++11
LIBS = -pthread

# clean
clean:
	rm *.out *.o



# client test modules
ClientTest: ClientTest.o Client.o Session.o select_helper.o net_helper.o NetworkEntityMultiplexer.o NetworkEntity.o
	$(CC) $(LIBS) -o ./ClientTest.out ClientTest.o Client.o Session.o select_helper.o net_helper.o NetworkEntityMultiplexer.o NetworkEntity.o

ClientTest.o: ClientTest.cpp
	$(CC) -c ClientTest.cpp

Client.o: Client.cpp Client.h
	$(CC) -c Client.cpp



# server test modules
ServerTest: ServerTest.o Server.o Session.o select_helper.o net_helper.o NetworkEntityMultiplexer.o NetworkEntity.o
	$(CC) $(LIBS) -o ./ServerTest.out ServerTest.o Server.o Session.o select_helper.o net_helper.o NetworkEntityMultiplexer.o NetworkEntity.o

ServerTest.o: ServerTest.cpp
	$(CC) -c ServerTest.cpp

Server.o: Server.cpp Server.h
	$(CC) -c Server.cpp




# shared helper modules
Session.o: Session.cpp Session.h
	$(CC) -c Session.cpp

select_helper.o: select_helper.cpp select_helper.h
	$(CC) -c select_helper.cpp

net_helper.o: net_helper.cpp net_helper.h
	$(CC) -c net_helper.cpp

NetworkEntityMultiplexer.o: NetworkEntityMultiplexer.cpp NetworkEntityMultiplexer.h
	$(CC) -c NetworkEntityMultiplexer.cpp

NetworkEntity.o: NetworkEntity.cpp NetworkEntity.h
	$(CC) -c NetworkEntity.cpp

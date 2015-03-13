
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
ServerTest: ServerTest.o Server.o ReceiveProcess.o select_helper.o Session.o net_helper.o
	$(CC) $(LIBS) -o ./ServerTest.out ServerTest.o Server.o ReceiveProcess.o select_helper.o Session.o net_helper.o

Server.o: Server.cpp Server.h
	$(CC) -c Server.cpp

ReceiveProcess.o: ReceiveProcess.cpp ReceiveProcess.h
	$(CC) -c ReceiveProcess.cpp

# fd_recv.o: fd_recv.c ancillary.h
# 	$(CC) -c fd_recv.c

# fd_send.o: fd_send.c ancillary.h
# 	$(CC) -c fd_send.c

select_helper.o: select_helper.c select_helper.h
	$(CC) -c select_helper.c

net_helper.o: net_helper.c net_helper.h
	$(CC) -c net_helper.c

# shared helper modules
Session.o: Session.cpp Session.h
	$(CC) -c Session.cpp

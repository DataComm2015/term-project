  # the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  #  -Wall turns on most, but not all, compiler warnings
  #  -std=c++11 sets compiler to use c++ 2011 standard
  #  -pthread for using linux pthreads
  CFLAGS  = -Wall -std=c++11 -pthread


 server: server_pro.o message_q.o
	 $(CC) $(CFLAGS) -o server server_pro.o message_q.o

 server_pro.o : server_pro.cpp
	$(CC) $(CFLAGS) -c server_pro.cpp


 client: client_pro.o message_q.o
	 $(CC) $(CFLAGS) -o client client_pro.o message_q.o

 client_pro.o : client_pro.cpp
	$(CC) $(CFLAGS) -c client_pro.cpp

test: message_q.o test.o
	 $(CC) $(CFLAGS) -o test test.o message_q.o

 clean:
	$(RM) client server test *.o *.exe

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

message_q.o: message_q.cpp
	$(CC) $(CFLAGS) -c message_q.cpp

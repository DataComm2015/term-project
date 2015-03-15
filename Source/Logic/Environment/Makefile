# Enemy Hierarchy Test Makefile

CC=g++ -std=c++11 -ggdb -W -pedantic 

COMPILE_FILES=EnemyHierarchy.o Driver.o

htest: $(COMPILE_FILES)
	$(CC) -o htest $(COMPILE_FILES)

clean:
	rm -f *.o core.* htest*

%.o: %.cpp
	$(CC) -c $< -o $@
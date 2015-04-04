# Deity ability casting Test Makefile

CC=g++ -ggdb -Wall -Wextra -pedantic -std=c++0x

deitytest: AbilityManager.o CastAbility.o TrainingDummy.o
	$(CC) -o deitytest AbilityManager.o CastAbility.o TrainingDummy.o

clean:
	rm -f *.o core.* deitytest*

CastAbility.o:
	$(CC) -c CastAbility.cpp

TrainingDummy.o:
	$(CC) -c TrainingDummy.cpp

AbilityManager.o:
	$(CC) -c AbilityManager.cpp
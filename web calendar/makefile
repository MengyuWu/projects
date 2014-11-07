CC=gcc
CCFLAGS = -Wall –lm

steps: CreateAccount.c 
	$(CC) $(CFLAGS) -o CreateAccount.exe CreateAccount.c
all:
	gcc -c MainProject1.h MainProject1.c
	gcc -o MainProject1.exe MainProject1.o	
	gcc -c CreateAccount.c 
	gcc -o CreateAccount.exe CreateAccount.o
	g++ -c find1.h find1.cpp
	g++ -o find1.exe find1.o
	g++ -c addgroupmeet.h addgroupmeet.cpp
	g++ -o addgroupmeet.exe addgroupmeet.o 
clean:
	rm -f *.o *.exe
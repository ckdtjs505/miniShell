main: main.o makeCommend.o makeToken.o execCommend.o
		gcc -g -o main main.o makeCommend.o makeToken.o execCommend.o
main.o: main.c makeCommend.h makeToken.h execCommend.h
        gcc -g -c main.c
makeCommend.o: makeCommend.h makeCommend.c
        gcc -g -c makeCommend.h makeCommend.c
makeToken.o: makeToken.h makeToken.c
        gcc -g -c makeToken.h makeToken.c
execCommend.o: execCommend.h execCommend.c
        gcc -g -c execCommend.h execCommend.c

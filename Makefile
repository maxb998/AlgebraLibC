
all: main.o MatBase.o AlgebraSequential.o AlgebraAVX.o
	gcc main.o MatBase.o AlgebraSequential.o AlgebraAVX.o -o main

main.o: main.c
	gcc -c main.c

MatBase.o: MatBase.c
	gcc -c MatBase.c

AlgebraSequential.o: AlgebraSequential.c
	gcc -c AlgebraSequential.c 

AlgebraAVX.o: AlgebraAVX.c
	gcc -c -mavx2 AlgebraAVX.c

clean: 
	rm *.o main

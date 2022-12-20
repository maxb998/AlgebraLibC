
all: main.o MatBase.o BasicAlgebra.o
	gcc main.o MatBase.o BasicAlgebra.o -o main

main.o: main.c
	gcc -c main.c

MatBase.o: MatBase.c
	gcc -c MatBase.c

BasicAlgebra.o: BasicAlgebra.c
	gcc -c BasicAlgebra.c

clean: 
	rm *.o main


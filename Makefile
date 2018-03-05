all: test_regles

Formules.o: Formules.c Formules.h
	gcc -c Formules.c
	
Regles.o: Regles.c Regles.h Formules.h
	gcc -c Regles.c
	
Test_Regles.o: Test_Regles.c Regles.h Formules.h
	gcc -c Test_Regles.c

test_regles: Formules.o Regles.o Test_Regles.o
	gcc Formules.o Regles.o Test_Regles.o -o test_regles
	
clean: rm -f *.o

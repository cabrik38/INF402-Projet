#include <stdlib.h>
#include <stdio.h>

#include "Formules.h"

void afficher_formule_rec(Arbre A){
    if (A->lex.nature == VARIABLE){
        if (A->lex.var.N){
            printf("-X%d%d%d", A->lex.var.x, A->lex.var.y, A->lex.var.k);
        } else {
            printf("X%d%d%d", A->lex.var.x, A->lex.var.y, A->lex.var.k);
        }
    } else if (A->lex.nature == CONJONCTION){
        printf("(");
        afficher_formule_rec(A->gauche);
        printf(" * ");
        afficher_formule_rec(A->droit);
        printf(")");
    } else if (A->lex.nature == DISJONCTION){
        printf("(");
        afficher_formule_rec(A->gauche);
        printf(" + ");
        afficher_formule_rec(A->droit);
        printf(")");
    } else {
        printf("T");
    }
}

void afficher_formule(Arbre A){
    afficher_formule_rec(A);
    printf("\n");
}

/* A1 = X251 */
Arbre arbre1() {
	return creer_variable(2, 5, 1, 0);
}

/* A2 = -X4510 */
Arbre arbre2() {
	return creer_variable(4, 5, 10, 1);
}

/* A3 = -X000 . -X927 */
Arbre arbre3() {
	Arbre X1 = creer_variable(0, 0, 0, 1);
	Arbre X2 = creer_variable(9, 2, 7, 1);
	return creer_conjonction(X1, X2);
}

/* A4 = X000 + X1060 */
Arbre arbre4() {
	Arbre X1 = creer_variable(0, 0, 0, 0);
	Arbre X2 = creer_variable(1, 0, 6, 0);
	return creer_disjonction(X1, X2);
}

int main(int argc, char** argv){
    Arbre A1 = NULL;
	Arbre A2 = NULL;
	Arbre A3 = NULL;
	Arbre A4 = NULL;
	Arbre A5 = NULL;
	Arbre A6 = NULL;
	Arbre A7 = NULL;
	Arbre A8 = NULL;

	printf("A1 = ");
	A1 = arbre1();
	afficher_formule(A1);           /* A1 = X251 */

	printf("A2 = ");
	A2 = arbre2();
	afficher_formule(A2);           /* A2 = -X4510 */

	printf("A3 = ");
	A3 = arbre3();
	afficher_formule(A3);           /* A3 = -X000 . -X927 */

	printf("A4 = ");
	A4 = arbre4();
	afficher_formule(A4);           /* A4 = X000 + X1060 */

	printf("A5 = ");
	A5 = creer_disjonction(A1,A2);
	afficher_formule(A5);           /* A5 = X251 + -X4510 */

	printf("A6 = ");
	A6 = creer_conjonction(A5,A3);
	afficher_formule(A6);           /* A6 = (X251 + -X4510) . (-X000 . -X927) */

	printf("A7 = ");
	A7 = creer_disjonction(A4,A6);
	afficher_formule(A7);           /* A7 = (X000 + X1060) + ((X251 + -X4510) . (-X000 . -X927)) */

	printf("A8 = ");
	A8 = creer_conjonction(A7,A4);
	afficher_formule(A8);           /* A8 = ((X000 + X1060) + ((X251 + -X4510) . (-X000 . -X927))) . (X000 + X1060) */

#if 0
	liberer_arbre(A8);  printf("A8 effacer\n");
	liberer_arbre(A7);  printf("A7 effacer\n");
	liberer_arbre(A6);  printf("A6 effacer\n");
	liberer_arbre(A5);  printf("A5 effacer\n");
	liberer_arbre(A4);  printf("A4 effacer\n");
	liberer_arbre(A3);  printf("A3 effacer\n");
	liberer_arbre(A2);  printf("A2 effacer\n");
	liberer_arbre(A1);  printf("A1 effacer\n");
#endif
}

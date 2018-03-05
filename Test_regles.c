#include <stdlib.h>
#include <stdio.h>

#include "Formules.h"
#include "Regles.h"

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

int main(int argc, char** argv){
  
  return 0;
}

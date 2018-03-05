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
  Arbre A1=regle_case(1,1,2,5);
  afficher_formule(A1);
  Arbre A2=regle_ligne(2,3,4);
  afficher_formule(A2);
  Arbre A3=regle_ligne(6,3,9);
  afficher_formule(A3);
  Arbre A4=regle_colonne(3,4,5);
  afficher_formule(A4);
  Arbre A5=regle_colonne(0,0,1);
  afficher_formule(A5);
  Arbre A6=regle_sup(1,2,4,4,5);
  afficher_formule(A6);
  Arbre A7=regle_valeur(1,2,3);
  afficher_formule(A7);
  return 0;
}

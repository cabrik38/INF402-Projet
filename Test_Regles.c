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
  printf("Arbre 1: \n");
  Arbre A1=regle_case(1,1,5);
  afficher_formule(A1);
  printf("Arbre 2: \n");
  Arbre A2=regle_ligne(2,3,4);
  afficher_formule(A2);
  printf("Arbre 3: \n");
  Arbre A3=regle_ligne(6,3,9);
  afficher_formule(A3);
  printf("Arbre 4: \n");
  Arbre A4=regle_colonne(3,4,5);
  afficher_formule(A4);
  printf("Arbre 5: \n");
  Arbre A5=regle_colonne(0,1,1);
  afficher_formule(A5);
  printf("Arbre 6: \n");
  Arbre A6=regle_sup(1,2,4,4,5);
  afficher_formule(A6);
  printf("Arbre 7: \n");
  Arbre A7=regle_valeur(1,2,3);
  afficher_formule(A7);
  return 0;
}

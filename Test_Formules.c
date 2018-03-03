#include <stdlib.h>

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
        afficher_formule(A->gauche);
        printf(" * ");
        afficher_formule(A->droit);
        printf(")");
    } else if (A->lex.nature == DISJONCTION){
        printf("(");
        afficher_formule(A->gauche);
        printf(" + ");
        afficher_formule(A->droit);
        printf(")");
    } else {
        printf("T");
    }
}

void afficher_formule(Arbre A){
    afficher_formule_rec(A);
    printf("\n");
}

Arbre arbre1(){
    return creer_variable(2,5,1,0);
}

Arbre arbre2(){
    return creer_variable(4,5,10,1);
}

Arbre arbre3(){
    Arbre X1 = creer_variable(0,0,0,1);
    Arbre X2 = creer_variable(9,2,7,1);
    return creer_conjonction(X1,X2);
}

Arbre arbre4(){
    Arbre X1 = creer_variable(0,0,0,0);
    Arbre X2 = creer_variable(1,0,6,0);
    return creer_disjonction(X1,X2);
}

int main(int argc, char** argv){
    Arbre A1 = NULL;
    Arbre A2 = NULL;
    Arbre A3 = NULL;
    Arbre A4 = NULL;
    Arbre A5 = NULL;
    Arbre A6 = NULL;
    Arbre A7 = NULL;
    
    A1 = arbre1();
    afficher_formule(A1);
    
    A2 = arbre2();
    afficher_formule(A2);
    /*
    A3 = arbre3();
    afficher_formule(A3);
    
    A4 = arbre4();
    afficher_formule(A4);
    
    A5 = creer_disjonction(A1,A2);
    afficher_formule(A5);
    
    A6 = creer_conjonction(A5,A3);
    afficher_formule(A6);
    
    A7 = creer_disjonction(A4,A6);
    afficher_formule(A7);
    */
    
    liberer_arbre(A7);
    liberer_arbre(A6);
    liberer_arbre(A5);
    liberer_arbre(A4);
    liberer_arbre(A3);
    liberer_arbre(A2);
    liberer_arbre(A1);
}

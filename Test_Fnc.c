#include <stdlib.h>

#include "Formules.h"
#include "Fnc.h"

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

void afficher_clause(Clause* C){
    if (C == NULL){
        return;
    }
    printf("C = ");
    afficher_formule(C->a);
}

void afficher_liste(Liste L){
    printf("Liste a %d elements\n", L.longueur);
    Clause* c = L.tete;
    int i = 0;
    for (c != NULL){
        printf("L[%d]: C = ", i);
        afficher_formule(c->a);
        printf("\n");
        i++;
        c = c->suivant;
    }
    printf("Fin de la liste\n");
}

/* A1 = X255 */
Arbre arbre1(){
    return creer_variable(2,5,5,0);
}

/* A2 = X255 + X485 + -X112 */
Arbre arbre2(){
    Arbre A = creer_disjonction(creer_variable(2,5,5,0), creer_variable(4,8,5,0));
    A = creer_disjonction(A, creer_variable(1,1,2,1));
    return A;
}

/* A3 = X111 + -X222 + X333 + X444 + -X555 + X666 */
Arbre arbre3(){
    Arbre A = creer_disjonction(creer_variable(1,1,1,0), creer_variable(2,2,2,1));
    A = creer_disjonction(A, creer_variable(3,3,3,0));
    A = creer_disjonction(A, creer_variable(4,4,4,0));
    A = creer_disjonction(A, creer_variable(5,5,5,1));
    A = creer_disjonction(A, creer_variable(6,6,6,0));
    return A;
}

int main(int argc, char** argv){
    Arbre A1 = arbre1();
    Arbre A2 = arbre2();
    Arbre A3 = arbre3();
    
    Liste L1;
    Liste L2;
    
    Clause* C1 = creer_clause(A1);
    Clause* C2 = creer_clause(A2);
    Clause* C3 = creer_clause(A3);
    
    ajouter_clause(&L1, C1);
    afficher_liste(L1);
    
    ajouter_clause(&L1, C2);
    afficher_liste(L1);
    
#if 0
    Clause* C4 = creer_clause(A3);
    Clause* C5 = creer_clause(A1);
    
    ajouter_clause(&L2, C4);
    afficher_liste(L2);
    
    ajouter_clause(&L2, C5);
    afficher_liste(L2);
    
    ajouter_liste(&L2, L1);
    afficher_liste(L2);    
#endif

    vider_liste(&L2);
    vider_liste(&L1);
    liberer_arbre(A3);
    liberer_arbre(A2);
    liberer_arbre(A1);
}

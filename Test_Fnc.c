#include <stdlib.h>
#include <stdio.h>

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
    while (c != NULL){
        printf("L[%d]: C = ", i);
        afficher_formule(c->a);
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

/* A4 = A1 . A2 */
Arbre arbre4(){
    return creer_conjonction(arbre1(),arbre2());
}

/* A5 = A3 . A2 . A1 */
Arbre arbre5(){
    return creer_conjonction(arbre3(),arbre4());
}

/* A6 = (A1 + A2) . A3 . A2 . A2 */
Arbre arbre6(){
    Arbre A = creer_disjonction(arbre1(),arbre2());
    A = creer_conjonction(A,arbre3());
    A = creer_conjonction(A,arbre2());
    A = creer_conjonction(A,arbre2());
    return A;
}

/* A7 = (X111 . X222) + X333 */
Arbre arbre7(){
    Arbre A = creer_conjonction(creer_variable(1,1,1,0), creer_variable(2,2,2,0));
    A = creer_disjonction(A, creer_variable(3,3,3,0));
    return A;
}

/* A8 = (X111 . X222) + (X333 . X444) */
Arbre arbre8(){
    Arbre A1 = creer_conjonction(creer_variable(1,1,1,0), creer_variable(2,2,2,0));
    Arbre A2 = creer_conjonction(creer_variable(3,3,3,0), creer_variable(4,4,4,0));
    Arbre A = creer_disjonction(A1, A2);
    return A;
}

/* A9 = A2 + (X333 . X444) */
Arbre arbre9(){
    Arbre A = creer_conjonction(creer_variable(3,3,3,0), creer_variable(4,4,4,0));
    A = creer_disjonction(arbre2(), A);
    return A;
}

/* A10 = A9 + (A3 . A1) */
Arbre arbre10(){
    Arbre A = creer_conjonction(arbre3(), arbre4());
    A = creer_disjonction(arbre9(), A);
    return A;
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
    Arbre A9 = NULL;
    Arbre A10 = NULL;
    
    Liste L1;
    Liste L2;
    Liste L3;
    Liste L4;
    Liste L5;    
    
    A1 = arbre1();
    A2 = arbre2();
    A3 = arbre3();
        
    Clause* C1 = creer_clause(A1);
    Clause* C2 = creer_clause(A2);
    Clause* C3 = creer_clause(A3);
    
    /* --- Test ajouter_clause() --- */
    printf("Test ajouter_clause()\n");
    
    printf("L1.1: ");
    ajouter_clause(&L1, C1);
    afficher_liste(L1);
    
    printf("L1.2: ");
    ajouter_clause(&L1, C2);
    afficher_liste(L1);
    
    /* --- Test ajouter_liste() --- */
    printf("Test ajouter_liste()\n");
    
    Clause* C4 = creer_clause(A3);
    Clause* C5 = creer_clause(A1);
    
    printf("L2.1: ");
    ajouter_clause(&L2, C4);
    afficher_liste(L2);
    
    printf("L2.2: ");
    ajouter_clause(&L2, C5);
    afficher_liste(L2);
    
    printf("L2.3: ");
    ajouter_liste(&L2, L1);
    afficher_liste(L2);
    
    /* --- Test clauses() --- */
    printf("Test clauses()\n");
    
    printf("L3: ");
    A4 = arbre4();
    L3 = clauses(A4);
    afficher_liste(L3);
    
    printf("L4: ");
    A5 = arbre5();
    L4 = clauses(A5);
    afficher_liste(L4);
    
    printf("L5: ");
    A6 = arbre6();
    L5 = clauses(A6);
    afficher_liste(L5);
    
    /* --- Test fnc() --- */
    printf("Test fnc()\n");
    
    // Littéral isolé
    printf("A1 = ");
    afficher_formule(A1);
    int f1 = fnc(A1);
    printf("FNC %d : ", f1);
    afficher_formule(A1);
    
    // Clause
    printf("A3 = ");
    afficher_formule(A3);
    int f3 = fnc(A3);
    printf("FNC %d : ", f3);
    afficher_formule(A3);
    
    // FNC
    printf("A4 = ");
    afficher_formule(A4);
    int f4 = fnc(A4);
    printf("FNC %d : ", f4);
    afficher_formule(A4);
    
    // A transformer
    printf("A7 = ");
    A7 = arbre7();
    afficher_formule(A7);
    int f7 = fnc(A7);
    printf("FNC %d : ", f7);
    afficher_formule(A7);
    
    printf("A8 = ");
    A8 = arbre8();
    afficher_formule(A8);
    int f8 = fnc(A8);
    printf("FNC %d : ", f8);
    afficher_formule(A8);
    
    printf("A9 = ");
    A9 = arbre9();
    afficher_formule(A9);
    int f9 = fnc(A9);
    printf("FNC %d : ", f9);
    afficher_formule(A9);
    
    printf("A10 = ");
    A10 = arbre10();
    afficher_formule(A10);
    int f10 = fnc(A10);
    printf("FNC %d : ", f10);
    afficher_formule(A10);

#if 0
    vider_liste(&L5);
    vider_liste(&L4);
    vider_liste(&L3);
    vider_liste(&L2);
    vider_liste(&L1);
    liberer_arbre(A10);
    liberer_arbre(A9);
    liberer_arbre(A8);
    liberer_arbre(A7);
    liberer_arbre(A6);
    liberer_arbre(A5);
    liberer_arbre(A4);
    liberer_arbre(A3);
    liberer_arbre(A2);
    liberer_arbre(A1);
#endif
    return 0;
}

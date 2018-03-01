#include "Formules.h"

Arbre creer_variable(int i, int j, int k, int neg){
    Arbre n = creer_noeud();
    n->lex.nature = VARIABLE;
    n->lex.var.x = i;
    n->lex.var.y = j;
    n->lex.var.k = k;
    n->lex.var.N = neg;
    return n;
}

Arbre creer_conjonction(Arbre A1, Arbre A2){
    Arbre n = creer_noeud();
    n->lex.nature = CONJONCTION;
    n->gauche = A1;
    n->droit = A2;
    return n;
}

Arbre creer_disjonction(Arbre A1, Arbre A2){
    Arbre n = creer_noeud();
    n->lex.nature = DISJONCTION;
    n->gauche = A1;
    n->droit = A2;
    return n;
}

Arbre creer_noeud(){
    Arbre n = (Arbre) malloc(sizeof(Noeud));
    return n;
}

void liberer_arbre(Arbre A){
    if (A == NULL){
        return;
    }
    liberer_arbre(A->gauche);
    liberer_arbre(A->droit);
    free(A);
}

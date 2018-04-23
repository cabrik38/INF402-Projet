#include "DPLL.h"

#include <stdlib.h>

NoeudVar* creer_noeudVar(Variable v){
    NoeudVar* n = (NoeudVar*) malloc(sizeof(NoeudVar));
    n->var = v;
    n->suivant = NULL;
    return n;
}

void init_listeVar(ListeVar* L){
    if (L == NULL){
        return;
    }
    L->longueur = 0;
    L->tete = NULL;
}

void ajouter_variable(ListeVar* L, Variable v){
    if (L == NULL){
        return;
    }
    NoeudVar* n = creer_noeudVar(v);
    n->suivant = L->tete;
    L->tete = n;
}

void liste_variable(ListeVar* L, Arbre A){
    if (A == NULL){
        return;
    } else if (A->nature == VARIABLE){
        ajouter_variable(L, A->var);
    } else {
        liste_variable(L, A->gauche);
        liste_variable(L, A->droit);
    }
}

int estIdentique(Variable v1, Variable v2){
    if ((v1.x == v2.x) && (v1.y == v2.y) && (v1.k == v2.k) && (v1.N == v2.N)){
        return 1;
    } else {
        return 0;
    }
}

int estNegation(Variable v1, Variable v2){
    if ((v1.x == v2.x) && (v1.y == v2.y) && (v1.k == v2.k) && (v1.N != v2.N)){
        return 1;
    } else {
        return 0;
    }
}

int estValide(ListeVar* L){
    if (L == NULL) { return -1; }
    NoeudVar* ni = L->tete;
    while (ni != NULL){
        NoeudVar* nj = ni->suivant;
        while (nj != NULL){
            if (estNegation(ni->var, nj->var)){
                return 1;
            }
            nj = nj->suivant;
        }
        ni = ni->suivant;
    }
    return 0;
}

int contient(ListeVar* Lc, ListeVar* Lb){
    if (Lc == NULL || Lb == NULL){ return -1; }
    NoeudVar* ni = Lc->tete;
    while (ni != NULL){
        int inclus = 0;
        NoeudVar* nj = Lb->tete;
        while (nj != NULL && inclus == 0){
            if (estIdentique(ni->var, nj->var)){
                inclus = 1;
            }
            nj = nj->suivant;
        }
        if (inclus == 0){
            return 0;
        }
        ni = ni->suivant;
    }
    return 1;
}
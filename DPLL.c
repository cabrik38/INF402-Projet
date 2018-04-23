#include "DPLL.h"

#include "Formules.h"

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

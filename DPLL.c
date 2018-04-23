#include "DPLL.h"

NoeudVar* creer_noeudVar(Variable v){
    NoeudVar* n = (NoeudVar*) malloc(sizeof(NoeudVar));
    n->suivant = NULL;
    return n;
}

void init_listeVar(ListeVar* L){
    L->longueur = 0;
    L->tete = NULL;
}

void ajouter_variable(ListeVar* L, Variable v){
    NoeudVar* n = creer_noeudVar(v);
    n->suivant = L->tete;
    L->tete = n;
}

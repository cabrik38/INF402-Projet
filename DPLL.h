#ifndef H_DPLL
#define H_DPLL

#include "Formules.h"

typedef struct NoeudVar {
    Variable var;
    struct NoeudVar *suivant;
} NoeudVar;

typedef struct ListeVar {
    int longueur;
    NoeudVar *tete;
} ListeVar;

NoeudVar* creer_noeudVar(Variable v);
void init_liste(ListeVar* L);
void ajouter_variable(ListeVar* L, Variable v);
void liste_variable(ListeVar* L, Arbre A);
int estIdentique(Variable v1, Variable v2);
int estNegation(Variable v1, Variable v2);
int estValide(ListeVar* L);
int contient(ListeVar* Lc, ListeVar* Lb);

#endif

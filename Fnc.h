#ifndef H_FNC
#define H_FNC

#include "Formules.h"

typedef struct Clause {
    Arbre a;
    struct Clause* suivant;
} Clause;

typedef struct Liste {
    int longueur;
    Clause* tete;
    Clause* queue;
} Liste;

Liste clauses(Arbre A);
int fnc(Arbre A);

Clause* creer_clause(Arbre A);
void ajouter_clause(Liste* list, Clause* cl);
void ajouter_liste(Liste* list, Liste cls);

#endif

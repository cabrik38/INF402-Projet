#ifndef H_FNC
#define H_FNC

#include "Formules.h"

typedef struct Clause {
    Arbre a;
    struct Clause* suivant;
} Clause;

typedef Clause* Liste;

Liste clauses(Arbre A);
int fnc(Arbre A);

#endif

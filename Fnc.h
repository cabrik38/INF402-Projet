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

/* --------------------
    fnc(A)
    > Transforme une formule (exprimée sous la forme d'un arbre A) en forme normale conjonctive FNC.
      Renvoie: -  1 si la formule obtenue est une FNC (avec au moins une conjonction)
               -  0 s'il s'agit d'une clause (ou d'un littéral isolé).
               - -1 en cas d'erreur
   -------------------- */
int fnc(Arbre *F);

/* --------------------
    clauses(A)
    > Renvoie la liste des clauses d'une FNC (exprimée sous la forme d'un arbre A).
   -------------------- */
Liste clauses(Arbre A);

Clause* creer_clause(Arbre A);
void init_liste(Liste* L);
void ajouter_clause(Liste* L, Clause* C);
void ajouter_liste(Liste* L, Liste Cs);
void vider_liste(Liste* L);

#endif

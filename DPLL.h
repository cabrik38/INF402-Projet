#ifndef H_DPLL
#define H_DPLL

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

#endif

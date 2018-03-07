#ifndef H_DIMACS
#define H_DIMACS

#include "Formules.h"
#include "Fnc.h"
#include <stdio.h>

void generer_dimacs(Arbre A, char* nom_fichier, int n);
void ecrire_commentaire(char* commentaire, FILE* f);
void ecrire_clause(Clause* C, FILE* f, int n);
void ecrire_clause_rec(Arbre A, FILE* f, int n);
int numero_variable(Variable V, int n);
int nombre_variables(int n);

#endif

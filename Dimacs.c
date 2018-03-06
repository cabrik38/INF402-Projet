#include "Dimacs.h"

#include <stdlib.h>
#include <stdio.h>

void generer_dimacs(Arbre A, char* nom_fichier){
    File* F = NULL;
    F = fopen(nom_fichier, "w+");
    
    int fnc_res = fnc(&A);
    if (fnc_res == -1){
        printf("Erreur lors de la transformation en FNC\n");
        return;
    }
    Liste L = clauses(A);
        
    fprintf(F, "p cnf %d %d\n", nombre_variables(n), L.longueur);
    
    Clause* c = L.tete;
    while (c != NULL){
        ecrire_clause(c, F, n);
        c = c->suivant;
    }
    
    fclose(F);
}

void ecrire_commentaire(char* commentaire, FILE* f){
    if (f == NULL){
        return;
    }
    fprintf(f, "c %s\n", commentaire);
}

void ecrire_clause(Clause* C, FILE* f, int n){
    if (C == NULL || f == NULL){
        return;
    }
    ecrire_clause_rec(C->a, f, n);
    fprintf(f, "0\n");
}

void ecrire_clause_rec(Arbre A, FILE* f, int n){
    if (A == NULL || f == NULL){
        return;
    }
    if (A->lex.nature == VARIABLE){
        fprintf(f, "%d ", numero_variable(A->lex.var, n));
    } else {
        ecrire_clause_rec(A->gauche, f, n);
        ecrire_clause_rec(A->droit, f, n);
    }
}

int numero_variable(Variable V, int n){
    int numero = V.y * n * n + V.x * n + V.k;
    if (V.N == 0){
        return numero;
    } else {
        return -numero;
    }
}

int nombre_variables(int n){
    return (n-1)*n*n + (n-1)*n + n;
}

#include "Fnc.h"

Liste clauses(Arbre A){
    if (A == NULL){
        return NULL;
    }
    if (A->lex.nature != DISJONCTION){
        return creer_clause(A);
    } else {
        Liste list = creer_clause(A->gauche);
        list->suivant = creer_clause(A->droit);
        return list;
    }
}

int fnc(Arbre A){
    if (A == NULL){
        return -1;
    }
    if (A->lex.nature == VARIABLE){
        return 0;
    } else {
        int g = fnc(A->gauche);
        int d = fnc(A->droit);
        if (A->lex.nature == DISJONCTION){
            if (g == 0 && d == 0){
                return 0;
            } else if (g == 0 && d == 1){
                Liste l_clauses = clauses(A->droit);
                
                return 1;
            } else if (g == 1 && d == 0){
                
                return 1;
            } else if (g == 1 && d == 1){
                
                return 1;
            } else {
                return -1;
            }
        } else {
            return 1;
        }
    }
}

Liste creer_clause(Arbre A){
    Liste c = (Liste) malloc(sizeof(Clause));
    c->a = A;
    c->suivant = NULL;
    return c;
}

#include "Fnc.h"

Liste clauses(Arbre A){
    List list;
    list.longueur = 0;
    if (A != NULL){
        if (A->lex.nature != DISJONCTION){
            ajouter_clause(&list, creer_clause(A));
        } else {
            ajouter_liste(&list, clauses(A->gauche));
            ajouter_liste(&list, clauses(A->droit));
        }
    }
    return list;
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
                for (int i = 0; i < l_clauses.longueur; i++){
                    
                }
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

void ajouter_clause(Liste* list, Clause* cl){
    if (list == NULL || cl == NULL){
        return;
    }
    if (list->queue == NULL){
        return;
    }
    list->queue->suivant = cl;
    list->queue = cl;
    list->longueur++;
}

void ajouter_liste(Liste* list, Liste cls){
    if (list == NULL){
        return;
    }
    if (list->queue == NULL || cls.tete == NULL){
        return;
    }
    list->queue->suivant = cls.tete;
    list->queue = cls.queue;
    list->longueur += cls.longueur;
}

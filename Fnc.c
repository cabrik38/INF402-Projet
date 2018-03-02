#include "Fnc.h"

Liste clauses(Arbre A){
    List list;
    init_liste(&list);
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
                Liste lc_d = clauses(A->droit);
                Arbre Ag = A->gauche;
                Clause* cl = lc_d.tete;
                while (cl != NULL){
                    Arbre Af = creer_disjonction(Ag, cl->a);
                    A = creer_conjonction(A, Af);
                    cl = cl->suivant;
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

Clause* creer_clause(Arbre A){
    Clause* c = (Clause*) malloc(sizeof(Clause));
    c->a = A;
    c->suivant = NULL;
    return c;
}

void init_liste(Liste* list){
    if (list == NULL){
        return;
    }
    list->longueur = 0;
    list->tete = NULL;
    list->queue = NULL;
}

void ajouter_clause(Liste* list, Clause* cl){
    if (list == NULL || cl == NULL){
        return;
    }
    if (list->longueur == 0){
        list->tete = cl;
    } else if (list->tete == NULL || list->queue == NULL){
        return;
    } else {
        list->queue->suivant = cl;
    }
    list->queue = cl;
    list->longueur++;
}

void ajouter_liste(Liste* list, Liste cls){
    if (list == NULL){
        return;
    }
    if (cls.longueur == 0 || cls.tete == NULL || cls.queue == NULL){
        return;
    }
    if (list->longueur == 0){
        list->tete = cls.tete;
    } else if (list->tete == NULL || list->queue == NULL){
        return;
    } else {
        list->queue->suivant = cls.tete;
    }
    list->queue = cls.queue;
    list->longueur += cls.longueur;
}

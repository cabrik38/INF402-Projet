#include "Fnc.h"

#include <stdlib.h>

int fnc(Arbre *F){
    Arbre A = *F;
    int return_value;
    if (A == NULL){
        return -1;
    }
    if (A->lex.nature == VARIABLE || A->lex.nature == TOP || A->lex.nature == BOTTOM){
        /* Si la formule est un littéral isolé, la fonction renvoie 0. */
        return_value = 0;
    } else {
        /* Si la formule est complexe (plusieurs littéraux), les sous-arbres gauche et droit sont transformés en FNC. */
        int g = fnc(&(A->gauche));
        int d = fnc(&(A->droit));
        if (A->lex.nature == CONJONCTION){
            /* Si la racine de l'arbre A est une conjonction, la formule est déjà une FNC. */
            return_value = 1;
        } else {
            /* Si la racine de l'arbre A est une disjonction : */
            if (g == 0 && d == 0){
                /* Si les sous-arbres gauche et droit représentent des clauses, alors l'arbre A représente une clause. */
                return_value = 0;
            } else if (g == 0 && d == 1){
                /* A = G + D1...Dn      où G et Di sont des clauses
                   A = (G + D1).(G + D2)...(G + Dn) */
                Liste lc_d = clauses(A->droit);
                Arbre Ag = A->gauche;
                A = NULL;
                Clause* c = lc_d.tete;
                while (c != NULL){
                    Arbre D = creer_disjonction(Ag, c->a);
                    A = creer_conjonction(A, D);
                    c = c->suivant;
                }
                vider_liste(&lc_d);
                return_value = 1;
            } else if (g == 1 && d == 0){
                /* A = G1...Gn + D      où Gi et D sont des clauses
                   A = (G1 + D).(G2 + D)...(Gn + D) */
                Liste lc_g = clauses(A->gauche);
                Arbre Ad = A->droit;
                A = NULL;
                Clause* c = lc_g.tete;
                while (c != NULL){
                    Arbre D = creer_disjonction(Ad, c->a);
                    A = creer_conjonction(A, D);
                    c = c->suivant;
                }
                vider_liste(&lc_g);
                return_value = 1;
            } else if (g == 1 && d == 1){
                /* A = G1...Gn + D1...Dn      où Gi et Di sont des clauses
                   A = (G1 + D1)...(G1 + Dn).(G2 + D1)...(G2 + Dn)...(Gn + Dn) */
                Liste lc_g = clauses(A->gauche);
                Liste lc_d = clauses(A->droit);
                A = NULL;
                Clause* cg = lc_g.tete;
                while (cg != NULL){
                    Clause* cd = lc_d.tete;
                    while (cd != NULL){
                        Arbre D = creer_disjonction(cg->a, cd->a);
                        A = creer_conjonction(A, D);
                        cd = cd->suivant;
                    }
                    cg = cg->suivant;
                }
                vider_liste(&lc_g);
                vider_liste(&lc_d);
                return_value = 1;
            } else {
                /* Erreur lors de la transformation en FNC du sous-arbre gauche ou droit */
                return -1;
            }
        }
    }
    *F = A;
    return return_value;
}

Liste clauses(Arbre A){
    Liste list;
    init_liste(&list);
    if (A != NULL){
        if (A->lex.nature != CONJONCTION){
            /* Si A est une clause ou un littéral isolé, la clause créée à partir de A est ajoutée à la liste */
            ajouter_clause(&list, creer_clause(A));
        } else {
            /* Si A est une FNC, la listes des clauses des enfant gauche et droit de A sont toutes deux ajoutées à la liste */
            ajouter_liste(&list, clauses(A->gauche));
            ajouter_liste(&list, clauses(A->droit));
        }
    }
    return list;
}

Clause* creer_clause(Arbre A){
    Clause* c = (Clause*) malloc(sizeof(Clause));
    c->a = A;
    c->suivant = NULL;
    return c;
}

void init_liste(Liste* L){
    if (L == NULL){
        return;
    }
    L->longueur = 0;
    L->tete = NULL;
    L->queue = NULL;
}

void ajouter_clause(Liste* L, Clause* C){
    if (L == NULL || C == NULL){
        return;
    }
    if (L->longueur == 0){
        L->tete = C;
    } else if (L->tete == NULL || L->queue == NULL){
        return;
    } else {
        L->queue->suivant = C;
    }
    L->queue = C;
    L->longueur++;
}

void ajouter_liste(Liste* L, Liste Cs){
    if (L == NULL){
        return;
    }
    if (Cs.longueur == 0 || Cs.tete == NULL || Cs.queue == NULL){
        return;
    }
    if (L->longueur == 0){
        L->tete = Cs.tete;
    } else if (L->tete == NULL || L->queue == NULL){
        return;
    } else {
        L->queue->suivant = Cs.tete;
    }
    L->queue = Cs.queue;
    L->longueur += Cs.longueur;
}

void vider_liste(Liste* L){
    Clause* c = L->tete;
    Clause* next = NULL;
    while (c != NULL){
        next = c->suivant;
        free(c);
        c = next;
    }
    init_liste(L);
}

#include "Fnc.h"

Liste clauses(Arbre A){
    List list;
    init_liste(&list);
    if (A != NULL){
        if (A->lex.nature != DISJONCTION){
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

int fnc(Arbre A){
    if (A == NULL){
        return -1;
    }
    if (A->lex.nature == VARIABLE || A->lex.nature == TOP || A->lex.nature == BOTTOM){
        /* Si la formule est un littéral isolé, la fonction renvoie 0. */
        return 0;
    } else {
        /* Si la formule est complexe (plusieurs littéraux), les sous-arbres gauche et droit sont transformés en FNC. */
        int g = fnc(A->gauche);
        int d = fnc(A->droit);
        if (A->lex.nature == CONJONCTION){
            /* Si la racine de l'arbre A est une conjonction, la formule est déjà une FNC. */
            return 1;
        } else {
            /* Si la racine de l'arbre A est une disjonction : */
            if (g == 0 && d == 0){
                /* Si les sous-arbres gauche et droit représentent des clauses, alors l'arbre A représente une clause. */
                return 0;
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
                return 1;
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
                return 1;
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
                return 1;
            } else {
                /* Erreur lors de la transformation en FNC du sous-arbre gauche ou droit */
                return -1;
            }
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

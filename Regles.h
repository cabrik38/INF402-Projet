#ifndef H_REGLES
#define H_REGLES

#include "Structures.h"

/* ------------------------------
    regle_case(i,j)
    > Renvoie l'arbre correspondant à la formule logique Vij (cf. Info.txt)
   ------------------------------ */
Arbre regle_case(int i, int j);

/* ------------------------------
    regle_ligne(i)
    > Renvoie l'arbre correspondant à la formule logique Li (cf. Info.txt)
   ------------------------------ */
Arbre regle_ligne(int i);

/* ------------------------------
    regle_colonne(j)
    > Renvoie l'arbre correspondant à la formule logique Cj (cf. Info.txt)
   ------------------------------ */
Arbre regle_colonne(int j);

/* ------------------------------
    regle_sup(a,b,c,d)
    > Renvoie l'arbre correspondant à la formule logique S? (cf. Info.txt)
   ------------------------------ */
Arbre regle_sup(int a, int b, int c, int d);

/* ------------------------------
    regle_valeur(i,j,k)
    > Renvoie l'arbre correspondant à la formule logique B? (cf. Info.txt)
   ------------------------------ */
Arbre regle_valeur(int i, int j, int k);

#endif

#ifndef H_REGLES
#define H_REGLES

#include "Formules.h"

/* ------------------------------
    regle_case(i,j)
    > Renvoie l'arbre correspondant à la formule logique Vij (cf. Info.txt)
   ------------------------------ */
Arbre regle_case(int i, int j, int n);

/* ------------------------------
    regle_ligne(i,k)
    > Renvoie l'arbre correspondant à la formule logique Li (cf. Info.txt)
   ------------------------------ */
Arbre regle_ligne(int i, int k, int n);

/* ------------------------------
    regle_colonne(j,k)
    > Renvoie l'arbre correspondant à la formule logique Cj (cf. Info.txt)
   ------------------------------ */
Arbre regle_colonne(int j, int k, int n);

/* ------------------------------
    regle_sup(a,b,c,d)
    > Renvoie l'arbre correspondant à la formule logique S? (cf. Info.txt)
   ------------------------------ */
Arbre regle_sup(int a, int b, int c, int d, int n);

/* ------------------------------
    regle_valeur(i,j,k)
    > Renvoie l'arbre correspondant à la formule logique B? (cf. Info.txt)
   ------------------------------ */
Arbre regle_valeur(int i, int j, int k);

#endif

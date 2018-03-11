/*  ---------------------------------------
    ---------  INF402 - FUTOSHIKI  --------
    ---------------------------------------
    --- ANDRE Stephen                   ---
    --- CHLOUS Clément                  ---
    --- DESPORTES Dorian                ---
    --------------------------------------- */

#include <stdlib.h>

#include "Formules.h"
#include "Lecture_Fichiers.h"
#include "Dimacs.h"

int main(int argc, char** argv){
    if (argc != 3){
        printf("Nombre d'arguments invalide : %s <fichier_entree> <fichier_sortie>\n", argv[0]);
        return -1;
    }
    int n;
    Arbre A = Lecture_grille(argv[1], &n);
    generer_dimacs(A, argv[2], n);
    return 0;
}

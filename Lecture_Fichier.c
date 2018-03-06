//
// Created by Clement on 05/03/2018.
//

#include "Lecture_Fichier.h"
#include "Formules.h"
#include <stdlib.h>
#include <stdio.h>

#include "Regles.h

Arbre Lecture_grille(char* nom_fichier){
    int i, n;
    char caractere;
    FILE *grille;
    grille = fopen(nom_fichier, "r");
    Arbre F = null;
    Arbre Ri = null;

    if (grille != NULL) {
        n=fgetc(grille);                                        // Convertir le char en int ('0' =/= 0)

        while ((caractere = fgetc(grille)) != EOF){             // Pas besoin de ça
            for(y=0; y<n; y++){
                for(x=0; x<n;x++){
                    caractere = fgetc(grille);
                    Ri = regle_valeur(x, y, caractere);         // regle_valeur seulement si le caractère n'est pas 0
                    F = creer_conjonction(F, Ri);
                    caractere = fgetc(grille);
                    switch (caractere){
                        case " ":
                            break;
                        case"<":
                            Ri=regle_sup(x+1,y,x,y);            // sup() prend un 5e param : la taille de la grille n
                            F=creer_conjonction(F,Ri);
                            break;
                        case ">":
                            Ri = regle_sup(x,y,x+1,y);          // sup() prend un 5e param : la taille de la grille n
                            F=creer_conjonction(F,Ri);
                            break;

                    }

                }

            }
        }
        fclose(grille);
    }
}

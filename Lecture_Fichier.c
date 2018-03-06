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
        n=fgetc(grille);

        while ((caractere = fgetc(grille)) != EOF){
            for(y=0; y<n; y++){
                for(x=0; x<n;x++){
                    caractere = fgetc(grille);
                    Ri = regle_valeur(x, y, caractere);
                    F = creer_conjonction(F, Ri);
                    caractere = fgetc(grille);
                    switch (caractere){
                        case " ":
                            break;
                        case"<":
                            Ri=regle_sup(x+1,y,x,y);
                            F=creer_conjonction(F,Ri);
                            break;
                        case ">":
                            Ri = regle_sup(x,y,x+1,y);
                            F=creer_conjonction(F,Ri);
                            break;

                    }

                }

            }
        }
        fclose(grille);
    }
};

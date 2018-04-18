//
// Created by Clement on 05/03/2018.
//

#include "Lecture_Fichier.h"
#include <stdlib.h>
#include <stdio.h>

#include "Regles.h"

Arbre Lecture_grille(char* nom_fichier, int* pn){
    int i,x,y,n;
    char caractere;
    char ligne[50];
    FILE *grille;
    grille = fopen(nom_fichier, "r");
    Arbre F = NULL;
    Arbre Ri = NULL;

    if (grille != NULL) {
        if (fgets(ligne, 50, grille) == NULL){
            printf("Ligne manquante\n");
            exit(-1);
        }
        n = ligne[0]-'0';
        if (n > 9 || n < 1){
            printf("La taille de la grille doit être comprise entre 1 et 9\n");
            exit(-1);
        }
        *pn = n;

        for(y=0; y<n; y++){
            for(x=0; x<n; x++){
                Ri = regle_case(x,y,n);
                F = creer_conjonction(F, Ri);
            }
        }
        for(y=0; y<n; y++){
            for(x=1; x<=n; x++){
                Ri = regle_colonne(y,x,n);
                F = creer_conjonction(F, Ri);
            }
        }
        for(y=0; y<n; y++){
            for(x=1; x<=n; x++){
                Ri = regle_ligne(y,x,n);
                F = creer_conjonction(F, Ri);
            }
        }

        for(y=0; y<n*2-1; y++){
            if (fgets(ligne, 50, grille) == NULL){
                printf("Ligne manquante\n");
                exit(-1);
            }
            x = 0;
            i = 0;
            if (y%2 == 0){
                while (x < n && ligne[i] != '\0'){
                    if (ligne[i] >= '0' && ligne[i] <= '9'){
                        if (ligne[i] != '0'){
                            int k = ligne[i] - '0';
                            Ri = regle_valeur(x, y, k);
                            F = creer_conjonction(F, Ri);
                        }
                        x++;
                    } else if (ligne[i] == '<'){
                        Ri = regle_sup(x+1,y,x,y,n);
                        F = creer_conjonction(F,Ri);
                    } else if (ligne[i] == '>'){
                        Ri = regle_sup(x,y,x+1,y,n);
                        F = creer_conjonction(F,Ri);
                    } else if (ligne[i] == '\0'){
                        printf("Ligne %d trop courte\n", y);
                        exit(-1);
                    }
                    i++;
                }
            } else {
                while (x < n && ligne[i] != '\0'){
                    if (ligne[i] == '.'){
                        x++;
                    } else if (ligne[i] == 'v' || ligne[i] == 'V'){
                        Ri = regle_sup(x,y,x,y+1,n);
                        F = creer_conjonction(F,Ri);
                        x++;
                    } else if (ligne[i] == '^'){
                        Ri = regle_sup(x,y+1,x,y,n);
                        F = creer_conjonction(F,Ri);
                        x++;
                    } else if (ligne[i] == '\0'){
                        printf("Ligne %d trop courte\n", y);
                        exit(-1);
                    }
                    i++;
                }
            }
        }
        fclose(grille);
    }
    return F;
}

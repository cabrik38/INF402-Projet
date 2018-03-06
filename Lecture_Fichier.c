//
// Created by Clement on 05/03/2018.
//

#include "Lecture_Fichier.h"
#include "Formules.h"
#include <stdlib.h>
#include <stdio.h>

#include "Regles.h"

Arbre Lecture_grille(char* nom_fichier){
    int i,x,y,n;
    char caractere;
    FILE *grille;
    grille = fopen(nom_fichier, "r");
    Arbre F = null;
    Arbre Ri = null;

    if (grille != NULL) {
        n=fgetc(grille)-'0';// Convertir le char en int ('0' =/= 0)
        
        for(y=0,y<n,y++){
            for(x=0,x<n,x++){
                Ri = regle_case(x,y,n);
                F = creer_conjonction(F, Ri);

            }
        }
         for(y=0,y<n,y++){
            for(x=1,x<=n,x++){
                Ri = regle_ligne(y,x,n);
                F = creer_conjonction(F, Ri);
            }
        }
         for(y=0,y<n,y++){
            for(x=1,x<=n,x++){
                Ri = regle_colonne(y,x,n);
                F = creer_conjonction(F, Ri);
            }
        }
            
        for(y=0; y<n; y++){
                for(x=0; x<n;x++){
                    caractere = fgetc(grille);
                    if (caractere != '0'){                    
                    Ri = regle_valeur(x, y, caractere-'0');         // regle_valeur seulement si le caractère n'est pas 0
                    F = creer_conjonction(F, Ri);
                    }
                    caractere = fgetc(grille);
                    switch (caractere){
                        case ' ':
                            break;
                        case'<':
                            Ri=regle_sup(x+1,y,x,y,n);            // sup() prend un 5e param : la taille de la grille n
                            F=creer_conjonction(F,Ri);
                            break;
                        case '>':
                            Ri = regle_sup(x,y,x+1,y,n);          // sup() prend un 5e param : la taille de la grille n
                            F=creer_conjonction(F,Ri);
                            break;
                           
                    }
                }
                  for(x=0; x<n;x++){
                    caractere = fgetc(grille);
                    switch (caractere){
                        case ' ':
                            break;
                        case'^':
                            Ri=regle_sup(x,y+1,x,y,n);            // sup() prend un 5e param : la taille de la grille n
                            F=creer_conjonction(F,Ri);
                            break;
                        case 'v':
                        case 'V':
                            Ri = regle_sup(x,y,x,y+1,n);          // sup() prend un 5e param : la taille de la grille n
                            F=creer_conjonction(F,Ri);
                            break;
                           
                    }
                     fgetc(grille); 
                }
            

            }
        }
        fclose(grille);
    }
return F;
}

#include "Regles.h"

#include <stdlib.h>

Arbre regle_case(int i, int j, int n){
  Arbre V = NULL;
  Arbre var;
    for (int k=0;k<n;k++){
      Arbre P = NULL;
      for(int x=0;x<n;x++){
        if (k==x){
          var=creer_variable(i, j,x,0);
        }
        else{
          var=creer_variable(i,j,x,1);
        }
        P = creer_conjonction(P,var)
      }
      V = creer_disjonction(V,P);
    }
  }
  return V;
}


Arbre regle_ligne(int i,int k, int n){
  Arbre L=NULL;
  Arbre var;
  Arbre P=NULL;
    for(int x=0;x<n;x++){
        if(x==i){var=creer_variable(i,x,k,1);}
        else{var=creer_variable(i,x,k,0);}
      P=creer_conjonction(P,var);
    }
    L=creer_disjonction(L,P);
  return L;
}

Arbre regle_colonne(int j,int k, int n){
  Arbre C=NULL;
  Arbre var;
  Arbre P=NULL;
  for(int y=1;y<n+1;y++){
  {
    if (y==j) {var=creer_variable(y,j,k,1);}
    else{var=creer_variable(y,j,k,0);}
    P=creer_conjonction(P,var);
  }
  C=creer_disjonction(C,P);
  return C;
}

Arbre regle_sup(int a, int b, int c, int d,int n){
  Arbre P=NULL;
  Arbre S=NULL;
  for(int i=2;i<=n;i++){
    for(int j=1;j<i;j++){
        P=creer_conjonction(creer_variable(a,b,i,0),creer_variable(c,d,j,0));
        S=creer_disjonction(S,P);
    }
  }
  return S;
}

Arbre regle_valeur(int i, int j, int k){
  return creer_variable(i,j,k,0);

}

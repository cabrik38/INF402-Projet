#ifndef H_FORMULES
#define H_FORMULES

/* -----------------------------------------------------------
    (x, y) = coordonnées de la variable sur la grille
    k = valeur particulière de la case (de 1 à n)
    N = 1 s'il s'agit de la négation de la variable, 0 sinon
   ----------------------------------------------------------- */
typedef struct Variable {
    int x;
    int y;
    int k;
    int N;
} Variable;

typedef enum NatureLexeme { TOP, BOTTOM, VARIABLE, CONJONCTION, DISJONCTION } NatureLexeme;

typedef struct Lexeme {
    NatureLexeme nature;
    Variable var;
} Lexeme;

typedef struct Noeud {
    Lexeme lex;
    struct Noeud* gauche;
    struct Noeud* droit;
} Noeud;

typedef struct Noeud* Arbre;

/* --------------------
    creer_variable(i,j,k,neg)
    > Créer et renvoie un Arbre, constitué d'un seul noeud contenant la variable Xijk de coordonnées (i,j) et de valeur k.
      Si neg = 1, c'est la négation de cette variable qui est représentée.
   -------------------- */
Arbre creer_variable(int i, int j, int k, int neg);

/* --------------------
    creer_conjonction(A1,A2)
    > Renvoie l'arbre constitué de la conjonction des arbres A1 et A2
      La racine de l'arbre est une CONJONCTION et ses enfants gauche et droit sont respectivement A1 et A2.
   -------------------- */
Arbre creer_conjonction(Arbre A1, Arbre A2);

/* --------------------
    creer_disjonction(A1,A2)
    > Renvoie l'arbre constitué de la disjonction des arbres A1 et A2
      La racine de l'arbre est une DISJONCTION et ses enfants gauche et droit sont respectivement A1 et A2.
   -------------------- */
Arbre creer_disjonction(Arbre A1, Arbre A2);


Arbre creer_noeud();
void liberer_arbre(Arbre A);

#endif

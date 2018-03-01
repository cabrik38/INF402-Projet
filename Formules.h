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


Arbre creer_conjonction(Arbre A1, Arbre A2);
Arbre creer_disjonction(Arbre A1, Arbre A2);
Arbre creer_noeud();
void liberer_arbre(Arbre A);

#endif

#ifndef acab_structure
#define acab_structure

// TODO : mettre en majuscules les define 

struct sommet{
    int numero;
    float x;
    float y;
    float cout_estime; // Cette info là va pas changer, pour un sommet
                    // (voir comment faire si peut changer).
};
typedef struct sommet sommet;

struct arete{
    sommet *depart;
    sommet *arrivee;
    float temps_min;
    float temps_max;
};
typedef struct arete arete;

struct graphe{
    arete *tab;   // Ptet faire par liste d'adjacence pour gagner en complexité temporelle 
    float T;
    float vitesse; 
    // Pour utiliser A*, il va falloir que la vitesse soit constante 
    // sur tout le graphe, telle que v = d/t.
    int n;
    int m;
};
typedef struct graphe graphe; 

// Idée : on va construire un arbre des chemins. 
struct noeud{
    sommet *le_sommet;
    float date_acces;
    float cout_reel;
    float cout_estime_chemin;
    struct noeud *parent; // Le sommet d'où on vient.
    struct noeud *adelphe; // On fait une liste chaînée pck un parent 
                            // peut avoir plusieurs enfants.
    struct noeud *enfant; // L'un des sommets auxquels celui-ci mène.
    struct noeud *precedent_liste; // Pour faire une autre liste chaînée,
                                 // afin de trier les noeuds.
    struct noeud *suivant_liste; // Pour faire une autre liste chaînée,
                                 // afin de trier les noeuds.
};
typedef struct noeud noeud;

#endif

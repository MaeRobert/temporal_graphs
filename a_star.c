#include "structure.h"
#include "a_star.h"
// #include "gestion_fichiers_tentative2.c" 
#include <math.h>
#include <stdio.h>
#include "gestion_sortie.h"


arete *get(int i, int j, graphe G)
{
    return &G.tab[G.n * i + j];
}

bool au_bon_endroit_au_bon_moment(noeud actuel, arete arete_voisin) 
{
    if ((arete_voisin.temps_min <= actuel.date_acces) &&
        (arete_voisin.temps_max >= actuel.date_acces)) {
        return true;
    } else {
        return false;
    }
}

float distance(sommet s1, sommet s2) 
{
    int somme_carres =
        (s1.x - s2.x) * (s1.x - s2.x) + (s1.y - s2.y) * (s1.y - s2.y);
    return sqrt((double) somme_carres);
}

float calcul_date_acces(graphe G, noeud origine, arete arete_voisin)
{
    sommet voisin = *(arete_voisin.arrivee);
    return origine.date_acces +
         ((distance(*(origine.le_sommet), voisin)) / (G.vitesse));
}

float calcul_cout_estime_chemin(graphe G, noeud origine, arete arete_voisin)
{
    sommet voisin = *(arete_voisin.arrivee);
    return origine.date_acces +
         ((distance(*(origine.le_sommet), voisin)) / (G.vitesse))+
         voisin.cout_estime;
}

int verification_print(noeud *liste)
{
    int k = 0;
    while(liste != NULL && k<10){
        printf("%f\n", liste->cout_estime_chemin);
        liste = (liste->suivant_liste);
        k += 1;
    }
    return 0;
}

noeud *trouver_endroit_insertion(noeud *liste, noeud *x)
{
    while ((liste != NULL) && (liste->suivant_liste != NULL) && (liste->cout_estime_chemin < x->cout_estime_chemin)){
        *liste = *liste->suivant_liste;
    }

    return liste;
}

int insertion_liste_triee(noeud **liste, noeud *x)
{ 
    noeud *endroit_liste = trouver_endroit_insertion(*liste, x);

    if (endroit_liste != NULL){
    printf("dans fct insertion %d\n", (endroit_liste->le_sommet)->numero);
    }
    verification_print(*liste);


    if (endroit_liste == NULL){
        x->precedent_liste = NULL;
        x->suivant_liste = NULL;
        *liste = x;
    }

    else{
        // Il y a au moins un élément dans la liste 

        if (endroit_liste->suivant_liste == NULL){
            
            if (endroit_liste->cout_estime_chemin < x->cout_estime_chemin){
                // On insère à la fin de la liste, 
                // Il y a donc au moins un élément devant 

                endroit_liste->suivant_liste = x;
                x->precedent_liste = endroit_liste;
                x->suivant_liste = NULL;
            }
            else{
                // On insère à l'avant-dernier endroit de la liste,
                // Il y a donc potentiellement aucun élément devant.
                noeud *precedent = endroit_liste->precedent_liste;

                if (precedent == NULL){
                    *liste = x;
                    x->suivant_liste = endroit_liste;
                    x->precedent_liste = NULL;
                    endroit_liste->precedent_liste = x;
                }
                else{
                    precedent->suivant_liste = x; 
                    x->precedent_liste = precedent;
                    x->suivant_liste = endroit_liste;
                    endroit_liste->precedent_liste = x;
                }
            }
        }

        else{
            // On insère soit au milieu de la liste, 
            // Soit tout devant (mais il y a au moins un élément derrière)
            noeud *precedent = endroit_liste->precedent_liste;

            if (precedent == NULL){
                *liste = x;
                x->suivant_liste = endroit_liste;
                x->precedent_liste = NULL;
                endroit_liste->precedent_liste = x;
            }
            else{
                precedent->suivant_liste = x;
                x->precedent_liste = precedent;
                x->suivant_liste = endroit_liste;
                endroit_liste->precedent_liste = x;
            }
        }
    }

    return 0;
}


noeud *extraction_premier_element(noeud **liste)
{
    noeud *premier = *liste;
    if ((*liste)->suivant_liste == NULL){
        *liste = NULL;
    }
    else{
        noeud *suivant = (*liste)->suivant_liste;
        suivant->precedent_liste = NULL;
        *liste = suivant;
    }
    return premier;
}


float a_star(graphe G, sommet *s, sommet *t) 
{

    // Création de la racine de l'arbre.
    noeud racine;
    racine.le_sommet = s;
    racine.date_acces = 0;
    racine.cout_reel = 0;
    racine.cout_estime_chemin = s->cout_estime;
    racine.parent = NULL;
    racine.adelphe = &racine;
    racine.enfant = NULL;
    racine.suivant_liste = NULL;
    racine.precedent_liste = NULL;

    // Création de la liste qui va contenir les noeuds à explorer.
    noeud *liste = &racine;
    noeud noeud_actuel = racine;

    while ((liste != NULL) && (noeud_actuel.le_sommet->numero != t->numero)) {

        noeud_actuel = *extraction_premier_element(&liste);
        
        // Traitement des voisins du sommet actuel
        // On trouve les voisins actuels du sommet actuel
        for (int i=0 ; i<G.n ; i++) { 

                 
            arete *arete_voisin = get((noeud_actuel.le_sommet)->numero, i, G);   // Vérifier si dans le bon sens 

            if ((arete_voisin != NULL)  && (noeud_actuel.le_sommet->numero != t->numero)){
                // On vérifie que le voisin est là au bon moment
                if (au_bon_endroit_au_bon_moment(noeud_actuel, *arete_voisin)) {
                    // On créée un nouveau noeud
                    // Pour chacun, on calcule leur cout_estime_chemin
                    noeud voisin;
                    voisin.le_sommet = arete_voisin->arrivee; 
                    voisin.date_acces = calcul_date_acces(G, noeud_actuel, *arete_voisin);
                    voisin.cout_reel = calcul_date_acces(G, noeud_actuel, *arete_voisin);
                    voisin.cout_estime_chemin = calcul_cout_estime_chemin(G, noeud_actuel, *arete_voisin);
                    voisin.parent = &noeud_actuel;
                    voisin.adelphe = &racine; // a modifier pour que ok 
                    voisin.enfant = NULL;
                    voisin.precedent_liste = NULL;
                    voisin.suivant_liste = NULL;

                    // Puis on l'insère au bon endroit dans L
                    insertion_liste_triee(&liste, &voisin);
                    verification_print(liste);
                    printf("sommet actuel num %d\n", noeud_actuel.le_sommet->numero); 
                    printf("voisin num %d\n", voisin.le_sommet->numero); 
                    printf("voisin date acces %f\n", voisin.date_acces); 
                }
            }
        }

        // Une fois le traitement des voisins du sommet actuel fait,
        // la liste est (invariant de boucle) ordonnée dans l'ordre
        // croissant par rapport  aux cout_estime_chemin de ses noeuds.
        // On poursuit donc avec celui dont le cout semble le plus bas.
    }
    printf("%d\n", noeud_actuel.le_sommet->numero); 
    // trace_back_path(noeud_actuel); TODO régler pb ici 
    print_vertices(G.n);
    print_arcs(G);
    return noeud_actuel.date_acces;
}





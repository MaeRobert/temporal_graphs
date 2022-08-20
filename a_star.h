#include "structure.h"
// #include "gestion_fichiers_tentative2.c" 
#include <math.h>
#include <stdio.h>

// TODO : Makefile
// TODO : changer nom gestion_fichier


#ifndef acab_a_star
#define acab_a_star

#define true 1
#define false 0

typedef int bool;

arete *get(int i, int j, graphe G); 

bool au_bon_endroit_au_bon_moment(noeud actuel, arete arete_voisin);

float distance(sommet s1, sommet s2);

float calcul_date_acces(graphe G, noeud origine, arete arete_voisin);

float calcul_cout_estime_chemin(graphe G, noeud origine, arete arete_voisin);

int verification_print(noeud *liste);

noeud *trouver_endroit_insertion(noeud *liste, noeud *x);

int insertion_liste_triee(noeud **liste, noeud *x);

noeud *extraction_premier_element(noeud **liste);

float a_star(graphe G, sommet *s, sommet *t);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "a_star.h" 



void trace_back_path(noeud actuel)
{
    FILE *pointeur_sortie;
    pointeur_sortie = fopen("sortie1.txt", "w+");


    while (&actuel != NULL){
        fprintf(pointeur_sortie, "%d ", actuel.le_sommet->numero);
        actuel = *(actuel.parent);
    }

    fclose(pointeur_sortie);
}


void print_vertices(int n)
{
    FILE *vertices;
    vertices = fopen("vertices.txt", "w+");

    for (int i = 0 ; i < n ; i++){
        fprintf(vertices, "%d ", i);
    }

    fclose(vertices);
}


void print_arcs(graphe G) // TODO être
{
    FILE *arcs;
    arcs = fopen("arcs.txt", "w+");

    fprintf(arcs, "[");

    for (int i = 0 ; i < G.n*G.n ; i++){
        if (G.tab[i].temps_min != -1){ // Dans quel cas l'arete existe
            fprintf(arcs, "(%d,%d) ", G.tab[i].depart->numero, G.tab[i].arrivee->numero);
        }
    }

    fprintf(arcs, "]");

    fclose(arcs);
}
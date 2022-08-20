#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "a_star.h" 

#define BUFFER_SIZE 1024 // fixé haut comme ça pas de pb 


// Preparing the appropriate structure in order to 
// read the CSV file
struct input{
    int num1;
    int num2;
    float x1;
    float y1;
    float x2;
    float y2;
    float temps_min;
    float temps_max;
};
typedef struct input input;


void ParseCSV(int n, int m)
{
    // Preparation of the data structures that we will be using 

    arete *mat = (arete*) malloc(n*n*sizeof(arete));
    sommet *tab_sommets = (sommet*) malloc(n*sizeof(sommet));

    // Initialisation du tableau des sommets 
    for(int i = 0 ; i < n ; i ++){
            tab_sommets[i].numero = -2;
            tab_sommets[i].x = 1312;
            tab_sommets[i].y = 1312;
            tab_sommets[i].cout_estime = -2;
    }

    // Initialisation de la matrice d'adjacence 
    for(int i = 0 ; i < n*n ; i ++){
        mat[i].depart = 0;
        mat[i].arrivee = 0;
        mat[i].temps_min = -1;
        mat[i].temps_max = -1;
    }


    // Opening the CSV file
    FILE * pInput;
    char buf[BUFFER_SIZE];
    pInput = fopen("exemple1.csv," "r");


    // Reading the first line of the file
    fgets(buf, sizeof(buf), pInput);

    for (int i = 0 ; i < 3 ; i++){
        // Reading the lines of the file where there actually are values
        fgets(buf, sizeof(buf), pInput);

        // Parsing the CSV and initializing the string with the data read above
        char *tok = strtok(buf, ",");

        // Converting the data to the appropriate type
        row.num1 = atoi(tok);

        // Processing the other columns of the same line 
        char *tok = strtok(NULL, ","); 
        row.num2 = atoi(tok); 
        tok = strtok(NULL, ","); 
        row.x1 = atof(tok); 
        tok = strtok(NULL, ","); 
        row.y1 = atof(tok);
        tok = strtok(NULL, ","); 
        row.x2 = atof(tok); 
        tok = strtok(NULL, ","); 
        row.y2 = atof(tok);
        tok = strtok(NULL, ","); 
        row.temps_min = atof(tok); 
        tok = strtok(NULL, ","); 
        row.temps_max= atof(tok);
    }
}

int main()
{
    // Ouverture du fichier 
    FILE *pointeur_exemple;
    pointeur_exemple = fopen("exemple1.txt", "r");
    int n, m, T, s, f;
    float v;

    // On obtient le premier caractère du fichier, ie. la taille 
    // du graphe (en nombre de sommets)
    fscanf(pointeur_exemple, "%d %d %f %d %d %d", &n, &m, &v, &T, &s, &f); 

    arete *mat = (arete*) malloc(n*n*sizeof(arete));
    sommet *tab_sommets = (sommet*) malloc(n*sizeof(sommet));

    // Initialisation du tableau des sommets 
    for(int i = 0 ; i < n ; i ++){
            tab_sommets[i].numero = -2;
            tab_sommets[i].x = 1312;
            tab_sommets[i].y = 1312;
            tab_sommets[i].cout_estime = -2;
    }

    // Initialisation de la matrice d'adjacence 
    for(int i = 0 ; i < n*n ; i ++){
        mat[i].depart = 0;
        mat[i].arrivee = 0;
        mat[i].temps_min = -1;
        mat[i].temps_max = -1;
    }


    int num1,num2;
    float x1, y1, x2, y2, temps_min, temps_max;
    // Input contient m ligne 
    // Et sur chaque ligne y a : id, x, y sommet de depart ; id, x, y sommet arrivee ; temps min et max arete 
    for(int i = 0 ; i < m ; i++){

        // On initialise d'abord les sommets que l'on n'avait pas encore rencontrés
        fscanf(pointeur_exemple, "%d %d %f %f %f %f %f %f", &num1, &num2, &x1, &y1, &x2, &y2, &temps_min, &temps_max); 
        if (tab_sommets[num1].numero == -2){
            tab_sommets[num1].x = x1;
            tab_sommets[num1].y = y1;
            tab_sommets[num1].numero = num1;
        }
        if (tab_sommets[num2].numero == -2){
            tab_sommets[num2].x = x2;
            tab_sommets[num2].y = y2;
            tab_sommets[num2].numero = num2;
        }

        // Puis on met l'arete dans le tableau mat
        mat[n*num1+num2].depart = &tab_sommets[num1];
        mat[n*num1+num2].arrivee = &tab_sommets[num2];
        mat[n*num1+num2].temps_min = temps_min;
        mat[n*num1+num2].temps_max = temps_max;
    }


    // On peut alors créer le graphe en lui-même
    graphe G;
    G.n = n;
    G.m = m;
    G.vitesse = v;
    G.T = T;
    G.tab = mat;

    for (int i = 0 ; i < n ; i++){
        tab_sommets[i].cout_estime = distance(tab_sommets[i], tab_sommets[f]);
    }

    // Fin de la mise en place de l'exemple
    // On peut donc exécuter A*, maintenant.

    a_star(G, &tab_sommets[s], &tab_sommets[f]);

    // Pas oublier de free les pointeurs !

    // TODO : Gérer les free !
    /*
    free(G);
    free(tab_sommets);
    free(mat);
    */

   // DONE : être petite
   
    // Fermeture du fichier
    fclose(pointeur_exemple);
    return 0;
}
// Implémentation de l'algorithme de Prim pour ACM (Arebre Couvrant minimum)
// On utilise la matrice d'adjacence

#include <stdio.h>
#include <limits.h>

// nombre de sommets dans le graphe
#define V 5

// Trouver le sommet avec la clé minimale, depuis les sommets non ajoutés à L'ACM
// mstEns[] est vrai si le sommet est dans l'ACM
int mincle(int cle[], bool mstEns[])
{
   // Initialiser la valeur min infini
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (mstEns[v] == false && cle[v] < min)
         min = cle[v], min_index = v;

   return min_index;
}

// imprimer l'ACM depuis pred[]
int printMST(int pred[], int n, int graph[V][V])
{
   printf("arrête   poids\n");
   for (int i = 1; i < V; i++)
      //printf("%d - %d    %d \n", pred[i], i, graph[i][pred[i]]); car la matrice est symétrique
      printf("%d - %d    %d \n", pred[i], i, graph[pred[i]][i]);

}

// Construction de l'ACM avec la matrice d'adjacence
void primMST(int graph[V][V])
{
     int pred[V]; // garder trace de l'ACM construit
     int cle[V];   // valeurs des clés pour choisir l'arrête de poid min dans une coupe
     bool mstEns[V];  // les sommets n'appartenants pas à ACM

     // Initialiser toutes les clés à INFINI
     for (int i = 0; i < V; i++)
        cle[i] = INT_MAX, mstEns[i] = false;

     // 1er sommet (de départ) dans ACM
     cle[0] = 0;     //  clé 0 pour prendre ce sommet en 1er
     pred[0] = -1; // 1er sommet est la racine de l'ACM

     // ACM aura V sommet
     for (int count = 0; count < V-1; count++)
     {
        // choisir la clé min des sommets qui ne sont pas dans ACM
        int u = mincle(cle, mstEns);

        // on rajoute le sommet à l'ACM
        mstEns[u] = true;


        for (int v = 0; v < V; v++)

           // graph[u][v] non nul pour les sommets adjacents
           // mstEns[v] est false pour les sommets qui ne sont pas dans ACM
           // Màj de clé only si graph[u][v] < cle[v]
          if (graph[u][v] && mstEns[v] == false && graph[u][v] <  cle[v])
             pred[v]  = u, cle[v] = graph[u][v];
     }


     printMST(pred, V, graph);
}


int main()
{
   /* Exemple
            300
        _______________
       |               |
       |  100    200   |
      (0)-----(1)-----(2)
       |      / \      |
    170| 300/    \150  |80
       |  /        \   |
      (3)-------------(4)
            250          */
   int graph[V][V] = {{0, 100, 300, 170, 0},
                      {100, 0, 200, 300, 150},
                      {300, 200, 0, 0, 80},
                      {170, 300, 0, 0, 250},
                      {0, 150, 80, 250, 0},
                     };

    // solution
    primMST(graph);

    return 0;
}

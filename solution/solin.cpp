#include <stdio.h>
#include <omp.h>

// représentation d'un arc
struct Edge
{
	int src, dest, weight;
};

// représentation d'un graphee connexe, non-orienté et valué
struct Graph
{
	// V : nb sommets, E-> nb d'arêtes
	int V, E;

	// graphe : tableau d'arrêtes.
	// une arrête de src à dest est aussi une arrête de arrete à src
	// car le graphee est non-orienté
	Edge* arrete;
};

// sous ensemble d'union-find
struct subset
{
	int parent;
	int rang;
};


int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);


void boruvkaMST(struct Graph* graphe)
{
	omp_lock_t majlock;
	//import les données
	int V = graphe->V, E = graphe->E;
	Edge *arrete = graphe->arrete;

	// allocation en mémoire de V sous ensembles
	struct subset *subsets = new subset[V];

	// tableau pour stocker l'arrête min

	int *ar_min = new int[V];

	// création de V sous ensemble avec un élément
	#pragma omp parallel for
	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rang = 0;
		ar_min[v] = -1;
	}

	// init V arbres différents.
	// fin un seul arbre
	int numTrees = V;
	int MSTweight = 0;

	// combiner les composantes connexes jusqu'à ne plus avoir qu'une seule


	while (numTrees > 1)
	{
		//chercher l'arrête min pour une composante
    #pragma omp parallel for
		for (int i=0; i<E; i++)
		{
			// chercher les représentants des extrémités d'une arrête
			int set1 = find(subsets, arrete[i].src);
			int set2 = find(subsets, arrete[i].dest);

			// s'ils n'ont le même parent on continue
			if (set1 != set2){
				omp_set_lock(&majlock);
			    if (ar_min[set1] == -1 ||
					arrete[ar_min[set1]].weight > arrete[i].weight)
					ar_min[set1] = i;

				if (ar_min[set2] == -1 ||
					arrete[ar_min[set2]].weight > arrete[i].weight)
					ar_min[set2] = i;
				omp_unset_lock(&majlock);
			}

			//sinon on regarde si l'arrête est plus petite que celle trouvée à l'étape d'avant
			//entre set1 et set2
			else{
				continue;
			}
		}

		// on prend l'arrête trouvée
        //#pragma omp parallel for schedule(static)
		#pragma omp parallel for schedule(static) 
		for (int i=0; i<V; i++)
		{
			// vérifier si l'arrête min exist pour la composante connexe considéré
			if (ar_min[i] != -1)
			{
				int set1 = find(subsets, arrete[ar_min[i]].src);
				int set2 = find(subsets, arrete[ar_min[i]].dest);

				if (set1 == set2)
					continue;
				MSTweight += arrete[ar_min[i]].weight;
				printf("arrête %d-%d ajoutée dans l'arbre == %d \n",
					arrete[ar_min[i]].src, arrete[ar_min[i]].dest,
					arrete[ar_min[i]].weight);

				// unions des deux composantes connexes et
				Union(subsets, set1, set2);
				numTrees--;
			}
		}
		#pragma omp parallel for
		for (int i=0; i<V; i++){
			  ar_min[i]=-1;

		  }
	}

	printf("poids de l'arbre couvrant %d\n", MSTweight);
	return;
}

// Creation du graphe
struct Graph* createGraph(int V, int E)
{
	Graph* graphe = new Graph;
	graphe->V = V;
	graphe->E = E;
	graphe->arrete = new Edge[E];
	return graphe;
}


int find(struct subset subsets[], int i)
{
	// trouver la racine et faire de la racine le parent de i
	// (path compression)
	if (subsets[i].parent != i)
	subsets[i].parent =
			find(subsets, subsets[i].parent);

	return subsets[i].parent;
}


void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	// attacher l'arbre de plus petit rang au plus grand
	if (subsets[xroot].rang < subsets[yroot].rang)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rang > subsets[yroot].rang)
		subsets[yroot].parent = xroot;

	// si rangs égaux peu importe et incrementer le rang de la racine
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rang++;
	}
}


int main()
{

	/*
			10
		0------1
		| \	   |
	   6| 5\   |15
		|   \  |
		2------3
			4	 */
			/* Premier exemple arbre couvrant de poids 19*/
/**	int V = 4; // nb sommets
	int E = 5; // nb arrêtes
	struct Graph* graphe = createGraph(V, E);


	// ajouter arrête 0-1
	graphe->arrete[0].src = 0;
	graphe->arrete[0].dest = 1;
	graphe->arrete[0].weight = 10;

	// ajouter arrête 0-2
	graphe->arrete[1].src = 0;
	graphe->arrete[1].dest = 2;
	graphe->arrete[1].weight = 6;

	// ajouter arrête 0-3
	graphe->arrete[2].src = 0;
	graphe->arrete[2].dest = 3;
	graphe->arrete[2].weight = 5;

	// ajouter arrête 1-3
	graphe->arrete[3].src = 1;
	graphe->arrete[3].dest = 3;
	graphe->arrete[3].weight = 15;

	// ajouter arrête 2-3
	graphe->arrete[4].src = 2;
	graphe->arrete[4].dest = 3;
	graphe->arrete[4].weight = 4;**/


	/** Deuxième exemple arbre vouvrant de poids 37**/
  	struct Graph* graphe = createGraph(9, 14);

	// ajouter arrete 0-1

	graphe->arrete[0].src = 0;
	graphe->arrete[0].dest = 1;
	graphe->arrete[0].weight = 4;

	// ajouter arrete 1-2
	graphe->arrete[1].src = 1;
	graphe->arrete[1].dest = 2;
	graphe->arrete[1].weight = 8;


	// ajouter arrete 1-7
	graphe->arrete[2].src = 1;
	graphe->arrete[2].dest = 7;
	graphe->arrete[2].weight = 11;

	// ajouter arrete 0-7
	graphe->arrete[3].src = 0;
	graphe->arrete[3].dest = 7;
	graphe->arrete[3].weight = 8;

	// ajouter arrete 7-6
	graphe->arrete[4].src = 6;
	graphe->arrete[4].dest = 7;
	graphe->arrete[4].weight = 1;

	// ajouter arrete 7-8
	graphe->arrete[5].src = 7;
	graphe->arrete[5].dest = 8;
	graphe->arrete[5].weight = 7;

	// ajouter arrete 2-8
	graphe->arrete[6].src =2;
	graphe->arrete[6].dest = 8;
	graphe->arrete[6].weight = 2;

	// ajouter arrete 2-5
	graphe->arrete[7].src =2;
	graphe->arrete[7].dest = 5;
	graphe->arrete[7].weight = 4;


	// ajouter arrete 8-6
	graphe->arrete[8].src =8;
	graphe->arrete[8].dest = 6;
	graphe->arrete[8].weight = 6;


		   // ajouter arrete 2-3
	graphe->arrete[9].src =2;
	graphe->arrete[9].dest = 3;
	graphe->arrete[9].weight = 7;


	// ajouter arrete 3-5
	graphe->arrete[10].src =3;
	graphe->arrete[10].dest = 5;
	graphe->arrete[10].weight =14;

	// ajouter arrete 3-4
	graphe->arrete[11].src =3;
	graphe->arrete[11].dest = 4;
	graphe->arrete[11].weight =9;


	// ajouter arrete 4-5
	graphe->arrete[12].src =4;
	graphe->arrete[12].dest = 5;
	graphe->arrete[12].weight =10;

	// ajouter arrete 5-6
	graphe->arrete[13].src =5;
	graphe->arrete[13].dest = 6;
	graphe->arrete[13].weight =2;
	boruvkaMST(graphe);

	return 0;
}

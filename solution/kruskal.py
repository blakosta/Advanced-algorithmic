# Kruskal ACM

from collections import defaultdict

#Classe pour un graphe
class Graph:

    def __init__(self,sommets):
        self.V= sommets #No. de sommets
        self.graph = [] # le graphe


    # fonction pour ajouter une arrete
    # u,v sommet
    # w le poid de l'arrete
    def addArrete(self,u,v,w):
        self.graph.append([u,v,w])

    # fonction pour trouver l'ensemble de  i
    # avec compression de chemin
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    # fonction qui fait l'union de 2 ensembles de x et y

    def union(self, parent, rang, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        # rattacher toujours la racine du lus petit arbre a la racine de l'autre
        if rang[xroot] < rang[yroot]:
            parent[xroot] = yroot
        elif rang[xroot] > rang[yroot]:
            parent[yroot] = xroot
        # si meme rang on en prend un comme racine et on incremente
        # son rang

        else :
            parent[yroot] = xroot
            rang[xroot] += 1


    def KruskalMST(self):

        result =[] # trace de la construction de l'ACM

        i = 0 # indice pour les arretes stockees
        e = 0 # indice pour result

        #Etape 1:  tier les arretes dans l'ordre croissant de leurs poids
        self.graph.sort(key=lambda item: item[2])
        #print self.graph

        parent = [] ; rang = []

        # creer V ensemble avec un seul element
        for node in range(self.V):
            parent.append(node)
            rang.append(0)

        # on prend V-1 arretes
        while e < self.V -1 :

            # etape 2 : choisir l'arrete la plus petite et on incremente i pour
            #passer a l'arrete suivante
            u,v,w =  self.graph[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent ,v)

            # On regarde si l'arrete en cours a seulement une extremite dans une
            # composante connexe
            # on ajoute l'arrete si elle ne cree pas de cycle

            if x != y:
                # si x == y, u et v ont dans la meme composante connexe
                e = e + 1
                result.append([u,v,w])
                self.union(parent, rang, x, y)


        # affichage du contenu de result[] pour afficher l'ACM
        print "Les arretes de l'arbre couvrant de poid min "
        for u,v,poid  in result:
            print ("%d -- %d == %d" % (u,v,poid))


g = Graph(5)
g.addArrete(0, 1, 100)
g.addArrete(0, 3, 170)
g.addArrete(0, 2, 300)
g.addArrete(1, 2, 200)
g.addArrete(1, 3, 300)
g.addArrete(1, 4, 150)
g.addArrete(2, 4, 80)
g.addArrete(3, 4, 250)

g.KruskalMST()

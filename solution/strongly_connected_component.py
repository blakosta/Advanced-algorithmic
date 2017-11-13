
# construction de la matrice d'adjecence à partir d'un fichier
# @param : - filename le nom du fichier contenant la matrice

def construction_Mat(filename):
    matrice = np.genfromtxt(filename, delimiter=' ')
    return matrice

# construction du graphe à partir de la mtrice d'adjecence
# on suppose que les sommets ont des labels entiers
# key le sommet, value la liste des successeurs


def construction_graph(matrice):
    temp = np.array([[i for i in range(1,matrice.shape[0]+1)],]*matrice.shape[0])
    work = np.multiply(matrice,temp)
    cle = 1
    for row_index in range(work.shape[0]):
        graph[cle] = [int(a) for a in work[row_index,:] if a != 0 ]
        cle += 1
    return graph

# construction du graphe à partir de la mtrice d'adjecence
# on suppose que les sommets ont des labels entiers
# key le sommet, value la liste des prédecesseurs

def construction_tgraph( matrice):
    temp = np.array([[i for i in range(1,matrice.shape[1]+1)],]*matrice.shape[1])
    work = np.multiply(matrice,temp.transpose())
    cle = 1
    for column_index in range(work.shape[1]):
        T_graph[cle] = [int(a) for a in work[:, column_index] if a != 0]
        cle += 1
    return T_graph

# Parcours du graphe et marquer d'un "+" tout les successeurs de sommet_depart
# non marqué.
# @param : - sommet_depart

def Marquer_Plus(graph, sommet_depart):
    res.append(sommet_depart)
    if( len(graph.get(sommet_depart)) != 0):
        for succ in graph.get(sommet_depart):
            if(succ not in res):
                Marquer_Plus(graph, succ)
            else:
                continue

    else:
        return res
    return res

# Parcours du graphe et marquer d'un "-" tout les prédecesseurs de sommet_depart
# non marqué.
# @param : - sommet_depart

def Marquer_Moins(T_graph, sommet_depart):
    res.append(sommet_depart)
    if( len(T_graph.get(sommet_depart)) != 0):
        for pred in T_graph.get(sommet_depart):
            if(pred not in res):
                Marquer_Moins(T_graph, pred)
            else:
                continue
    else:
        return res
    return res

def Composantes_Fortement_Connexes(graph):

    for key in graph.keys():
        print("sommet de départ", key)
        explored_Plus = Marquer_Plus(graph, key)
        explored_Moins = Marquer_Moins(T_graph, key)
        print(explored_Plus)
        print(explored_Moins)
        cfc = list()
        for element in explored_Plus :
            if(element in explored_Moins) and (element in explored_Moins):
                cfc.append(element)
        print(cfc)



nomFichier = "./g1.txt" #filename with adjacency matrix 
mat_adj = construction_Mat(nomFichier)

graph = construction_graph(mat_adj)
print(graph)
T_graph = construction_tgraph(mat_adj)
print(T_graph)
Composantes_Fortement_Connexes(graph)

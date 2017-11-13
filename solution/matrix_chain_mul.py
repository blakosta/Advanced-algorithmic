import numpy as np

print("entrez les dimensions des matrices p1 p2...")
p = [int(i) for i in input().split()]
n = len(p)
# fonction poids

z = np.zeros((n,n), dtype="float")
# la position du meilleur parenthésage
b = np.zeros((n,n), dtype="i")

for l in range(2,n+1):
    for i in range(1,n-l+1):
        j = i+l-1
        z[i,j] = np.inf
        for k in range(i,j):
            temp = z[i,k] + z[k+1,j] + p[i-1]*p[k]*p[j]
            if(temp < z[i,j]):
                z[i,j] = temp
                b[i,j] = k
z = z[1:,1:]


# parenthésage

def parenthese(tab, i, j):
    if(i==j):
        print("A"+str(i),end='')
    else:
        print("(",end='')
        parenthese(tab,i,tab[i,j])
        parenthese(tab,tab[i,j]+1,j)
        print(")",end='')
print("\n")
print("parenthésage optimal")
parenthese(b,1,6)
print("\n")

########################################################################
# Given n elementary cubes (which are of the size 1), we can create    #
# sets (cube or pyramide). What's the minimum number of sets we can    #
# create using all the n elementary cubes ?                            #
########################################################################


print("enter the number of elementary cubes")
n = int(input())
# we use 1 to identify cubic forms
# and 2 for pyramides
tailleC = [ [k*k*k, 1] for k in range(1,n+1) if (k*k*k) <= n]
tailleP = [ [int((k*(k+1)*(2*k+1))/6), 2] for k in range(1,n+1)
                if int((k*(k+1)*(2*k+1))/6) <= n ]
# merge the two lists
t = tailleC + tailleP
# we sort in ascending order according to the first dimension of the
# list
t.sort(key = lambda x: x[0])
print("List of sizes in ascending order"+"\n" )
print(t)

z = [[0,0],[1,1]]
for i in range(2, n+1):
    z.append([z[i-1][0]+1 ,1])
    k = 1
    while( (k <= len(t)-1) and (t[k][0]<=i)):
        if((z[i-t[k][0]][0] + 1) < z[i][0]):
            z[i] = [z[i-t[k][0]][0] + 1,k]
        k += 1

value = n

tab = list()
while (value != 0):
	if (t[z[value][1]][1] == 1):
		tab.append("cube with a size of " + str(t[z[value][1]][0]))
	elif (t[z[value][1]][1] == 2):
		tab.append("pyramide with a size of " + str(t[z[value][1]][0]))

	value -= t[z[value][1]][0]

for i in range(len(tab)) :
    if (tab[i] == "pyramide with a size of 1"):
        tab[i] = "cube with a size of 1"

print("\n".join(tab))

#######################################################################
# Two examples of strings you could try X = "ABCBDAB", Y = "BDCABA".  #
# The longest common substring is BCBA                                #
#######################################################################

import numpy as np
print("enter the first string")
X = input()
print("enter the second string")
Y = input()

m = len(X)
n = len(Y)

c = np.zeros((m+1,n+1), dtype="i")
b = np.zeros((m+1,n+1), dtype="i")

for i in range(1,m+1):
    for j in range(1,n+1):
        if(X[i-1] == Y[j-1]):
            c[i,j] = c[i-1,j-1] + 1
            b[i,j] = 1
        elif(c[i-1,j] >= c[i,j-1]):
            c[i,j] = c[i-1,j]
            b[i,j] = 2
        else :
            c[i,j] = c[i,j-1]
            b[i,j] = 3
# The direction in which we move to get the solution
# 3 = left, 2 = up ,1 = diagonal
i = m
j = n
ls = ""
while (c[i,j] != 0):
    if (b[i,j] == 1):
        ls = X[i-1] + ls
        i -= 1
        j -= 1
    elif(b[i,j] == 2):
        i -= 1
    elif(b[i,j] == 3):
        j -= 1
print(c)

print(ls)

import numpy as np

a=np.random.choice([5,6,7,8,9,10], (9,9))
np.fill_diagonal(a,100)
print 9
for i in range(9):
	for j in range(9):
		print a[i][j],
	print ""
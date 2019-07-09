import numpy as np

density = np.loadtxt('density.txt')
cdf = np.loadtxt('density.txt')
datasize = 2097152
cdf[0] = density[0];
for i in range(1, datasize):
    cdf[i] = cdf[i - 1] + density[i]

np.savetxt('cdf.txt', cdf, fmt='%.12f')

import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import statsmodels.api as sm
from statsmodels.distributions.mixture_rvs import mixture_rvs


np.random.seed(12345)

dist1_loc, dist1_scale, weight1 = -1 , 0.5, 0.25
dist2_loc, dist2_scale, weight2 = 1 , 0.5, 0.75

datasize=2097152

# 拟合样本array数据
obs_dist = mixture_rvs(prob=[weight1, weight2], size=datasize, dist=[stats.norm, stats.norm],kwargs = (dict(loc=dist1_loc, scale=dist1_scale),dict(loc=dist2_loc, scale=dist2_scale)))

file = open('key.txt','w')

for key in obs_dist:
    file.write(str(key))
    file.write('\n')

file.close()


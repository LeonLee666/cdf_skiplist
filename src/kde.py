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
# 核密度估计，可得到 kde.support, kde.density 向量
kde = sm.nonparametric.KDEUnivariate(obs_dist)
kde.fit(kernel='gau')
#np.savetxt('key.txt',kde.support,fmt='%.12f')
#np.savetxt('density.txt',kde.density,fmt='%.12f')

# 计算2.5的cdf值
#print(kde.cdf[np.searchsorted(kde.support,2.5)])
#true_values = (stats.norm.pdf(loc=dist1_loc, scale=dist1_scale, x=kde.support)*weight1+ stats.norm.pdf(loc=dist2_loc, scale=dist2_scale, x=kde.support)*weight2)

#fig = plt.figure(figsize=(12, 5))
#ax = fig.add_subplot(111)
#ax.plot(kde.support, kde.cdf, lw=3, label='CDF')
#true_cdf = (stats.norm.cdf(loc=dist1_loc, scale=dist1_scale, x=kde.support)*weight1+ stats.norm.cdf(loc=dist2_loc, scale=dist2_scale, x=kde.support)*weight2)
#ax.plot(kde.support, true_cdf, lw=3, label='True CDF', zorder=15)
#ax.hist(obs_dist, bins=50, cumulative=True, density=True, label='Histogram from samples',zorder=5, edgecolor='k', alpha=0.5)
#ax.legend(loc = 'best')
#ax.grid(True, zorder=-5)
#fig.show()

# 样本集合
#print(np.sort(obs_dist))

#print(kde.support)
#print(kde.ay)
#print(true_cdf)

#fig = plt.figure(figsize=(12, 5))
#ax = fig.add_subplot(111)
#true_values = (stats.norm.pdf(loc=dist1_loc, scale=dist1_scale, x=kde.support)*weight1+ stats.norm.pdf(loc=dist2_loc, scale=dist2_scale, x=kde.support)*weight2)
#ax.hist(obs_dist, bins=20, density=True, label='Histogram from samples',zorder=5, edgecolor='k', alpha=0.5)
#ax.plot(kde.support, kde.density, lw=3, label='KDE from samples', zorder=10)
#ax.plot(kde.support, true_values, lw=3, label='True distribution', zorder=15)
#ax.legend(loc='best')
#ax.grid(True, zorder=-5)
#fig.show()



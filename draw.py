import numpy as np
from matplotlib.pyplot import contourf, gcf

M = np.loadtxt('points.dat', skiprows=1)

bins_x = 600
bins_y = 600
H, xedges, yedges = np.histogram2d(M[:,0], M[:,1], [bins_x, bins_y])

X, Y = np.meshgrid((xedges[1:] + xedges[:-1]) / 2,
                   (yedges[1:] + yedges[:-1]) / 2)


contourf(X, Y, H, cmap='jet')
fig = gcf()
fig.set_size_inches(13.66, 7.68)
fig.savefig('density.png', dpi=500)

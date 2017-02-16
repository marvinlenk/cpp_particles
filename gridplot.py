import numpy as np
import time as tm
import mpl_toolkits
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.animation as animation

plt.rcParams['animation.ffmpeg_path'] ='/usr/local/bin/ffmpeg'

params = np.loadtxt('./parameters.ini')
FFwriter = animation.FFMpegWriter(fps=params[3],extra_args=['-vcodec', 'libx264'],bitrate=-1)

fig = plt.figure(num=None, figsize=(10, 10), dpi=300)
ax = fig.add_subplot(111, projection='3d')
data = np.loadtxt('./grid.txt')
t0 = tm.time()
def iterate(n):
        m = int(n)
        ax.cla()
        plt.suptitle('t = ' + str( round( data[ int(m*params[0]) , 0 ], 2)) + 's')
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        ax.set_xlim3d(0,params[4])
        ax.set_ylim3d(0,params[5])
        ax.set_zlim3d(0,params[6])
        if m % (params[1]/10) == 0:
            print(m,'/',int(params[1]), round(tm.time()-t0,2),'s')
            
        for i in range(0,int(params[0])):
            pos = int(m*params[0] + i)
            ax.scatter(data[pos,1],data[pos,2],data[pos,3])
        return ax
    
ani = animation.FuncAnimation(fig, iterate, range(0,int(params[1])))
ani.save('./plot.mp4',writer=FFwriter)
plt.close()
print('plotting done')
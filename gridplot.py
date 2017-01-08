import numpy as np
import mpl_toolkits
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.animation as animation

plt.rcParams['animation.ffmpeg_path'] ='/usr/local/bin/ffmpeg'
FFwriter = animation.FFMpegWriter(fps=30,extra_args=['-vcodec', 'libx264'],bitrate=-1)

fig = plt.figure(num=None, figsize=(10, 10), dpi=300)
ax = fig.add_subplot(111, projection='3d')
data = np.loadtxt('./grid.txt')
def iterate(n):
        m = int(n)
        ax.cla()
        plt.suptitle('t = '+ str(n))
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        ax.set_xlim3d(0,1e3)
        ax.set_ylim3d(0,1e3)
        ax.set_zlim3d(0,1e3)
        if(m % (data[-1,0]/10) == 0):
            print(m,'/',(data[-1,0]))
        return ax.scatter(data[m,1],data[m,2],data[m,3])
    
ani = animation.FuncAnimation(fig, iterate, range(0,int(data[-1,0])))
ani.save('./plot.mp4',writer=FFwriter)
plt.close()
print('plotting done')
"""
Graficacion para un mapa 
de calor, usando Matplotlib
y Numpy.
"""

import numpy as np
import matplotlib.pyplot as plt
import math


def x_index(n):
    """Funcion encargada de crear indices en x
    para colocar los valores de la matriz de 
    calor
    """
    r = []
    for i in range (0,n):
        for j in range (0,n):
            r.append(j)
    return r


def y_index(n):
    """Funcion encargada de crear indices en y
    para colocar los valores de la matriz de 
    calor
    """
    r = []
    for i in range (0,n):
        for j in range (0,n):
            r.append(i)
    return r



def fix_x(n,m):
    """Arregla es descuadro de los valores x
    """
    r = []
    for i in range (0,n):
        for j in range (0,n):
            r.append(m[(n)*(n-1-j)+(i)])
    return r



def hm(z,e,u,v,r):
    """Esta funcion se encarga de graficar el mapa
    de calor para una matriz cuadrada con valores 
    de temperatura que van en un rango desde los
    -50 grados C, hasta los 400 grados C.
    """

    
    

    n = math.sqrt(len(z))
    x = x_index(int(n))
    y = y_index(int(n))

    x_f = fix_x(int(n),u)



  


    if (r):
	plt.quiver(x,y,u,v,scale=500, scale_units='inches')


    heatmap, xedges, yedges = np.histogram2d(y, x, bins = (n), weights=z)
    if e==1:
    	plt.imshow(heatmap, extent=[0,n,n,0],origin = 'upper', interpolation='nearest',
                   cmap='inferno',vmin=-50,vmax=400)
    else:
        plt.imshow(heatmap, extent=[0,n,n,0],origin = 'upper', interpolation='nearest',
                   cmap='inferno')
    cb = plt.colorbar()
    cb.set_label(label='Temperature(C)',weight='bold')
    fig = plt.gcf()
    fig.canvas.set_window_title('Heatmap ANPI')
    plt.show()


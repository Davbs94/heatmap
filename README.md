# Heatmap

Antes de ejecutar el programa se debe tener lo siguiente instalado:
-Python 2.7
-Numpy (si no lo tiene: sudo apt-get intall python-numpy)
-matplotlib (si no lo tiene: sudo apt-get intall python-matplotlib)

Para compilar el archivo main.cpp:
-g++ -std=c++11 main.cpp -fopenmp -lpython2.7

Para ejecutar el programa con parametros:
-./a.out (dimension de la matriz cuadrada) (Pared abajo) (Pared Arriba) (Pared Derecha) (Pared Izquierda)
(Escala: 0 para absoluta, 1 para relativa) (Mostrar flujo: 1 si, 0 no) (Correr con interfaz: 1 si, 0 no)

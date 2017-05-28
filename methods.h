#ifndef METHODS_H
#define METHODS_H

#include "matrix.h"
#include <vector>
#include <string>
#include <omp.h>

namespace methods {

    /**
     * @brief metodo que se encarga de inicializar una matriz con ceros
     * @param m: matriz a la cual se le desean insertar los ceros
     */
    template<typename T>
    void makeCero(anpi::Matrix<T>& m){
        for (unsigned int i = 0; i < m.rows(); i++){
            for (unsigned int j = 0; j < m.cols(); j++){
                m.insert(i,j,T(0));
            }
        }
    }

    /**
     * @brief metodo que se encarga de analizar los casos de los limites de la placa
     * @param n indica el numero de filas que va a tener la matriz
     * @param m indica el numero de columnas que va a tener la matriz
     * @param bottom indica la cantidad de calor que se va a aplicar al lado mas bajo de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param top indica la cantidad de calor que se va a aplicar al lado de arriba de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param left indica la cantidad de calor que se va a aplicar al lado izquierdo de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param right indica la cantidad de calor que se va a aplicar al lado derecho de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param m: matriz a la cual se le desean insertar los valores de los bordes
     */
    template<typename T>
    void insertBounderyValues(short int n, short int m, T bottom, T top, T left, T right, anpi::Matrix<T>& M){
        /**
         * se analizan los casos de los limites
         * Para el caso de la placa es sencillo dado el hecho de que solo se analizan los bordes
        */
        //en la parte baja de la placa
        for(int i = 0; i < m; i++){

                M.insert(m-1,i, bottom);
        }

        //en la parte alta de la placa
        for(int i = 0; i < m; i++){
            M.insert(0,i, top);
        }

        //en la parte izquierda de la placa
        for(int i = 0; i < n; i++){
                M.insert(i,0, left);
        }

        //en la parte derecha de la placa
        for(int i = 0; i < n; i++){
               M.insert(i,n-1, right);
        }
    }

    template<typename T>
    const char* convertToString(std::vector<T> V){
        std::string tmp = "z = [";
        for(unsigned int i = 0; i < V.size(); i++){
            if(i == V.size() - 1)
                tmp.append(std::to_string(V[i]) + "]");
            else
                tmp.append(std::to_string(V[i]) + ", ");
        }
        return tmp.c_str();
    }

    /**
     * @brief Este es el metodo utilizado para generar la matriz de solucion del metodo de leabman
     * @param n indica el numero de filas que va a tener la matriz
     * @param m indica el numero de columnas que va a tener la matriz
     * @param bottom indica la cantidad de calor que se va a aplicar al lado mas bajo de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param top indica la cantidad de calor que se va a aplicar al lado de arriba de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param left indica la cantidad de calor que se va a aplicar al lado izquierdo de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param right indica la cantidad de calor que se va a aplicar al lado derecho de la placa (el valor es constante por todo el lado),
     *                si el valor que se indica es 0, se asume que ese borde esta aislado
     * @param solution En este parametro se almacenara la solucion del metodo
     */
    template<typename T>
    void liebmann(short int n, short int m, T bottom, T top, T left, T right, std::vector<T>& solution)
    {
        /** se instancia una matriz en la cual se guardara la solucion del metodo*/
        anpi::Matrix<T> M(n,m);

        /** se llena con cero la matriz*/
        makeCero(M);

        /**
         * se analizan los casos de los limites
         * Para el caso de la placa es sencillo dado el hecho de que solo se analizan los bordes
        */
        insertBounderyValues(n, m, bottom, top, left, right, M);


        /**
        * Se aplica el metodo de liebmann
        * T[i][j] = (1/4)( T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1])
        * el metodo se iterera n veces
        */
        for(int k = 0; k < n*m; k++){
            for(int i = 1; i < n; i++){
                for(int j = 1; j < m; j++){
                    if(i+1 != n && j+1 != m){
                        /**
                         * @brief tmp:almacena el valor de la formula
                         */
                        T tmp = 0.25 * ( M.get(i+1,j) + M.get(i-1,j) + M.get(i,j+1) + M.get(i,j-1));
                        M.insert(i,j,tmp);
                    }
                }
            }
        }


        /**
        * Se guarda el resultado de la matriz en el vector solution
        */
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                solution[i*m+j] = (M.get(i,j));
            }
        }

    }

    template<typename T>
    void pliebmann(short int n, short int m, T bottom, T top, T left, T right, std::vector<T>& solution){

        /** se instancia una matriz en la cual se guardara la solucion del metodo*/
        anpi::Matrix<T> M(n,m);

        /** se llena con cero la matriz*/
        makeCero(M);

        /**
         * se analizan los casos de los limites
         * Para el caso de la placa es sencillo dado el hecho de que solo se analizan los bordes
        */
        insertBounderyValues(n, m, bottom, top, left, right, M);
		
        /**
        * Se aplica el metodo de liebmann
        * T[i][j] = (1/4)( T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1])
        * el metodo se iterera n veces
        */
        #pragma omp parallel
        {
            int i, j, k;
            T tmp = T(0);
            #pragma omp for
            for (k = 0; k < n; k++) {
                for (j = 1; j < n; j++) {
                    for (i = 1; i < n; i++) {
                        if(i+1 != n && j+1 != m){
                            /**
                             * @brief tmp: almacena el valor de la formula del metodo de liebmann
                             */
                            tmp = 0.25 * ( M.get(i+1,j) + M.get(i-1,j) + M.get(i,j+1) + M.get(i,j-1));
                             M.insert(i,j,tmp);
                        }
                    }
                }
            }
        }

        
		
		/**
        * Se guarda el resultado de la matriz en el vector solution
        */
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                solution[i*m+j] = (M.get(i,j));
            }
        }
    }
	

    template<typename T>
    void heatX(int n, int m, std::vector<T>& qx, std::vector<T> V){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if (j ==0 || i == 0){
                    qx.push_back(0);
                }

                else if (j == m-1 || i == n-1){
                    qx.push_back(0);
                }

                else{
                    T dx = -(V[((i*m)+j)+1] - V[((i*m)+j)-1]);
                    qx.push_back(dx/2);
                }
            }
        }
    }

    template<typename T>
    void heatY(int n, int m, std::vector<T>& qy, std::vector<T> V){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){

                if (i ==0 || j == 0){
                    qy.push_back(0);
                }

                else if (i == n-1 || j == m-1){
                    qy.push_back(0);
                }

                else{
                    T dy = (V[(m*(i+1)+j)] - V[(m*(i-1)+j)]);
                    qy.push_back(dy/2);
                }
            }
        }
    }


}


#endif // METHODS_H

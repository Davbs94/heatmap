#ifndef METHODS_H
#define METHODS_H

#include "matrix.h"
#include <vector>
#include <string>
#include <omp.h>

namespace methods {

	template<typename T>
    class Liebmann {
		private:
			/**
			 * @brief metodo que se encarga de inicializar una matriz con ceros
			 * @param m: matriz a la cual se le desean insertar los ceros
			 */
			void makeCero(anpi::Matrix<T>& m);
			
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
			void insertBounderyValues(short int n, short int m, T bottom, T top, T left, T right, anpi::Matrix<T>& M);
			
			const char* convertToString(std::vector<T> V);
		
			
			
		public:
			/**
			 * @brief Constructor
			*/
			Liebmann();
			
			/**
			 * @brief Destructor
			*/
			~Liebmann();
		
			/**
			 * @brief Este es el metodo utilizado para generar la matriz de solucion del metodo de liebman paralelizado
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
			void liebmann(short int n, short int m, T bottom, T top, T left, T right, std::vector<T>& solution);
		
			/**
			 * @brief Este es el metodo utilizado para generar la matriz de solucion del metodo de liebmann paralelizado
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
			void pliebmann(short int n, short int m, T bottom, T top, T left, T right, std::vector<T>& solution);
			
			/**
			 * @brief Este es el metodo utilizado para generar el vector qx, que representa la componente x del flujo del calor
			 * @param n indica el numero de filas que va a tener la matriz
			 * @param m indica el numero de columnas que va a tener la matriz
			 * @param qx vector representante de la componente x del flujo calorifico
			 * @param top indica la cantidad de calor que se va a aplicar al lado de arriba de la placa (el valor es constante por todo el lado),
			 *                si el valor que se indica es 0, se asume que ese borde esta aislado
			 * @param V representa el vector soluci[on del metodo de liebmann
			 */
			void heatX(int n, int m, std::vector<T>& qx, std::vector<T> V);
		
			/**
			 * @brief Este es el metodo utilizado para generar el vector qy, que representa la componente y del flujo del calor
			 * @param n indica el numero de filas que va a tener la matriz
			 * @param m indica el numero de columnas que va a tener la matriz
			 * @param qx vector representante de la componente y del flujo calorifico
			 * @param top indica la cantidad de calor que se va a aplicar al lado de arriba de la placa (el valor es constante por todo el lado),
			 *                si el valor que se indica es 0, se asume que ese borde esta aislado
			 * @param V representa el vector soluci[on del metodo de liebmann
			 */
			void heatY(int n, int m, std::vector<T>& qy, std::vector<T> V);

	}; //class liebman
	
	template<typename T>
    Liebmann<T>::Liebmann(){}
	
	template<typename T>
    Liebmann<T>::~Liebmann(){}
	
	
	/**
	 * @brief metodo que se encarga de inicializar una matriz con ceros
	 * @param m: matriz a la cual se le desean insertar los ceros
	 */
	template<typename T>
	void Liebmann<T>::makeCero(anpi::Matrix<T>& m){
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
	void Liebmann<T>::insertBounderyValues(short int n, short int m, T bottom, T top, T left, T right, anpi::Matrix<T>& M){
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
	const char* Liebmann<T>::convertToString(std::vector<T> V){
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
	 * @brief Este es el metodo utilizado para generar la matriz de solucion del metodo de liebmann
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
	void Liebmann<T>::liebmann(short int n, short int m, T bottom, T top, T left, T right, std::vector<T>& solution)
	{
		/** se instancia una matriz en la cual se guardara la solucion del metodo*/		
		anpi::Matrix<T> M(n,m);
		/** se instancia una matriz temporal en la cual se guardara la matriz anterior del metodo, para as[i hacer las comparaciones y obtener el error*/
		anpi::Matrix<T> TMP(n,m);

		/** se llena con cero la matriz*/
		makeCero(M);
		/** se llena con cero la matriz*/
		makeCero(TMP);

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
		for(int k = 0; k < n; k++){
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
			if(k == 1) TMP.fill(M.data());
			else if(k > 2){
				if (std::abs(TMP.norm() - M.norm()) < 0.001){ //verificacion del error con la norma
					break;
				}
				else{
					TMP.fill(M.data());
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

	/**
	 * @brief Este es el metodo utilizado para generar la matriz de solucion del metodo de leabman paralelizado
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
	void Liebmann<T>::pliebmann(short int n, short int m, T bottom, T top, T left, T right, std::vector<T>& solution){

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

	/**
	 * @brief Este es el metodo utilizado para generar el vector qx, que representa la componente x del flujo del calor
	 * @param n indica el numero de filas que va a tener la matriz
	 * @param m indica el numero de columnas que va a tener la matriz
	 * @param qx vector representante de la componente x del flujo calorifico
	 * @param top indica la cantidad de calor que se va a aplicar al lado de arriba de la placa (el valor es constante por todo el lado),
	 *                si el valor que se indica es 0, se asume que ese borde esta aislado
	 * @param V representa el vector soluci[on del metodo de liebmann
	 */
	template<typename T>
	void Liebmann<T>::heatX(int n, int m, std::vector<T>& qx, std::vector<T> V){
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

	/**
	 * @brief Este es el metodo utilizado para generar el vector qy, que representa la componente y del flujo del calor
	 * @param n indica el numero de filas que va a tener la matriz
	 * @param m indica el numero de columnas que va a tener la matriz
	 * @param qx vector representante de la componente y del flujo calorifico
	 * @param top indica la cantidad de calor que se va a aplicar al lado de arriba de la placa (el valor es constante por todo el lado),
	 *                si el valor que se indica es 0, se asume que ese borde esta aislado
	 * @param V representa el vector soluci[on del metodo de liebmann
	 */
	template<typename T>
    void Liebmann<T>::heatY(int n, int m, std::vector<T>& qy, std::vector<T> V){
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

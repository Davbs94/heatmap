#include <iostream>
#include "methods.h"
#include <vector>
#include <python2.7/Python.h>
#include <string>
#include <stdlib.h> 


int main(int argc, char* argv[])
{
    int n = atoi(argv[1])+1;
    int m = atoi(argv[1])+1;
    std::vector<double> V(n*m,0),qx,qy;
    methods::Liebmann<double> L;


    if (atoi(argv[9])||(atoi(argv[9])==2)){
    	double st=omp_get_wtime();
    	for (int i = 0; i < 50; i++) L.liebmann(atoi(argv[1])+1,atoi(argv[1])+1,atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]), V);
		double en=omp_get_wtime();
    	std::cout << "Serie  " << (en - st)/50 << std::endl;
	st=omp_get_wtime();
   	for (int i = 0; i < 50; i++) L.pliebmann(n,m,atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]), V);
		en=omp_get_wtime();
    	std::cout << "Paralelo  " << (en - st)/50 << std::endl;
    }
   
    
    if (atoi(argv[9])==0||(atoi(argv[9])==2)){
    	if (atoi(argv[8])){
        	L.liebmann(n,m,atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]), V);
        	L.heatX(n,m,qx,V);
       		L.heatY(n,m,qy,V);
        
    		std::string tmp1 = "z = [";
    		std::string tmp2 = "e = ";
    		std::string tmp3 = "u = [";
    		std::string tmp4 = "v = [";
    		std::string tmp5 = "r = ";
        	for(unsigned int i = 0; i < V.size(); i++){
            	if(i == V.size() - 1){
                	tmp1.append(std::to_string(V[i]) + "]");
         		tmp3.append(std::to_string(qx[i]) + "]");
			tmp4.append(std::to_string(qy[i]) + "]");		
	    	}
            	else{
               		tmp1.append(std::to_string(V[i]) + ", ");
                	tmp3.append(std::to_string(qx[i]) + ",");
			tmp4.append(std::to_string(qy[i]) + ",");
	   	}
        }

   
    
        tmp2.append(std::to_string(atoi(argv[6])));
        tmp5.append(std::to_string(atoi(argv[7])));
        /*
         *Codigo de Python embebido para graficar usando MatplotLib
        */

        const char * a = tmp1.c_str();
        const char * b = tmp2.c_str();
        const char * c = tmp3.c_str();
        const char * d = tmp4.c_str();
        const char * e = tmp5.c_str();
    
    

        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./')");
        PyRun_SimpleString("from HeatMap import *");
        PyRun_SimpleString(a);
        PyRun_SimpleString(b);
        PyRun_SimpleString(c);
        PyRun_SimpleString(d);
        PyRun_SimpleString(e);
        PyRun_SimpleString("hm(z,e,u,v,r)");
        Py_Exit(0);
        Py_Finalize();
        }
     }
    return 0;
}

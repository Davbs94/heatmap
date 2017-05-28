#include <iostream>
#include "methods.h"
#include <vector>
#include <python2.7/Python.h>
#include <string>
#include <stdlib.h> 


int main(int argc, char* argv[])
{
    std::vector<float> V,qx,qy;

    methods::liebmann<float>(atoi(argv[1]),atoi(argv[1]),atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]), V);
    methods::heatX<float>(atoi(argv[1]),atoi(argv[1]),qx,V);
    methods::heatY<float>(atoi(argv[1]),atoi(argv[1]),qy,V);

    std::string tmp1 = "z = [";
    std::string tmp2 = "e = ";
    std::string tmp3 = "u = [";
    std::string tmp4 = "v = [";
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
    /*
     *Codigo de Python embebido para graficar usando MatplotLib
     */

    const char * a = tmp1.c_str();
    const char * b = tmp2.c_str();
	const char * c = tmp3.c_str();
    const char * d = tmp4.c_str();

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString("from HeatMap import *");
    PyRun_SimpleString(a );
    PyRun_SimpleString(b );
	PyRun_SimpleString(c );
    PyRun_SimpleString(d );
    PyRun_SimpleString("hm(z,e,v,v)");
    Py_Exit(0);
    Py_Finalize();

    return 0;
}

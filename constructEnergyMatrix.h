//
// Created by chenjl on 2020/4/11.
//

#ifndef MUSTDO_CONSTRUCTENERGYMATRIX_H
#define MUSTDO_CONSTRUCTENERGYMATRIX_H

#include <map>
#include <string>

int constructEnergyMatrix(int L, double *H,int dim);
int constructEnergyMatrixPro(int L, map<string,double> & H,unsigned long long dim);

#endif //MUSTDO_CONSTRUCTENERGYMATRIX_H

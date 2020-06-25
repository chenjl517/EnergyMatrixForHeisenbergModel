//
// Created by chenjl on 2020/4/11.
//

#include <math.h>
#include "assert.h"
#include <iostream>
using namespace std;

int constructEnergyMatrix(int L, double *H,int dim){
    // this function will produce an energy matrix of Heisenberg spin chain with periodic boundary condition
    assert(pow(2,L)==dim);

    //SzSz
    double  SzBase[4]={0.25,-0.25,-0.25,0.25};

    for(int i=0;i<L-1;i++){
        //L-2 i L-2-i
        int Edim1=pow(2,i);
        int Edim2=pow(2,L-2-i);

        for(int j=0;j<Edim1;++j){

            //SzSz部分生成的结果是反对角线按一定周期重复的矩阵(重复Edim1次)
            for(int k=0;k<Edim2*4;++k){
                int tol=j*Edim2*4+k;
                H[tol*dim+tol]+=SzBase[k/Edim2];
            }


            //SxSx+SySy部分生成的结果是某两条次对角线为0.5的矩阵重复Edim1次
            int fixLowerOrigin=(j*Edim2*4+Edim2*2)*dim+j*Edim2*4+Edim2;
            int fixUpperOrigin=(j*Edim2*4+Edim2)*dim+j*Edim2*4+2*Edim2;
            for(int k=0;k<Edim2;++k){
                H[fixLowerOrigin+k*dim+k]+=0.5;
                H[fixUpperOrigin+k*dim+k]+=0.5;
            }

        }

    }

    //开边界条件下的矩阵构造完毕,下构造周期边界条件的附加项
    //SxSx+SySy
    int subMatrixDim=dim/2;
    int fixUpperOrigin=subMatrixDim;
    int fixLowerOrigin=subMatrixDim*dim;
    for(int k=0;k<subMatrixDim/2;++k){
        H[fixUpperOrigin+dim]+=0.5;
        fixUpperOrigin+=2*dim+2;

        H[fixLowerOrigin+1]+=0.5;
        fixLowerOrigin+=2*dim+2;
    }

    double tmp=0.25;
    for(int k=0;k<subMatrixDim;++k){
        H[k*dim+k]+=tmp;
        H[(k+subMatrixDim)*dim+(k+subMatrixDim)]+=-tmp;
        tmp*=(-1);
    }

    return 0;
}
# 计算Heisenberg模型的能量矩阵

最常规的计算哈密顿量的方法就是根据定义式计算直积，但是直接暴力直积很容易就内存炸了，而且速度也很慢。考虑到单位矩阵、$\frac{1}{2}(\hat{S_i^-}\hat{S_{i+1}^+}+\hat{S_i^+}\hat{S_{i+1}^-})$和$\hat{S_i^z}\hat{S_{i+1}^z}$的稀疏性， 最终哈密顿量的非零元素的坐标是可以通过类似解析的方式给出的。

下介绍$\frac{1}{2}(\hat{S_i^-}\hat{S_{i+1}^+}+\hat{S_i^+}\hat{S_{i+1}^-})$非零元素及其位置的具体生成方法：

首先，容易证明，单位矩阵与单位矩阵的直积依旧是单位矩阵，那么对于$L=n$的情况，$\frac{1}{2}(\hat{S_i^-}\hat{S_{i+1}^+}+\hat{S_i^+}\hat{S_{i+1}^-})=\frac{1}{2}(I_{(i-1)*(i-1)}\otimes\hat{S_i^-}\otimes\hat{S_{i+1}^+}\otimes I_{(n-i-1)*(n-i-1)})$,其中$I_k*k$代表$2^k*2^k$的单位矩阵。

下分析$I_{k*k}$与$S_{XYbase}=\frac{1}{2}(\hat{S_i^-}\hat{S_{i+1}^+}+\hat{S_i^+}\hat{S_{i+1}^-})$直积的效果

#### (i) $S_{XYbase}\otimes I_{k*k}$

$S_{XYbase}\otimes I_{k*k}=S_{XYbase}\otimes \left(\begin{matrix}1&0&\cdots&0\\0&1\\\vdots&&\ddots\\0&&\cdots&1\\\end{matrix}\right)_{2^k\times2^k}= \left(\begin{array}{ccc}\frac{1}{4} & 0 & 0&0 \\ 0 & -\frac{1}{4} & \frac{1}{2} &0 \\ 0 & \frac{1}{2} & -\frac{1}{4}&0 \\ 0 & 0 & 0 & \frac{1}{4}\end{array}\right) \otimes\left(\begin{matrix}1&0&\cdots&0\\0&1\\\vdots&&\ddots\\0&&\cdots&1\\\end{matrix}\right)_{2^k\times2^k}\\=\left(\begin{array}{ccc}\frac{1}{4} I_{k*k} & 0 & 0&0 \\ 0 & -\frac{1}{4}I_{k*k} & \frac{1}{2}I_{k*k} &0 \\ 0 & \frac{1}{2}I_{k*k} & -\frac{1}{4}I_{k*k}&0 \\ 0 & 0 & 0 & \frac{1}{4}I_{k*k}\end{array}\right)$

即单位矩阵从右边与矩阵$S_{XYbase}$直积相当于:

1. 沿对角线依次将对角元($\frac{1}{4}$、$-\frac{1}{4}$、$-\frac{1}{4}$、$\frac{1}{4}$)重复$2^k$遍；
2. 从$(2k,k)$、$(k、2k)$开始，沿着平行于对角线的方向将$\frac{1}{2}$重复k次(下标从0开始).

#### (ii)  $I_{k*k}\otimes A$

$I_{k*k}\otimes A=\left(\begin{matrix}1&0&\cdots&0\\0&1\\\vdots&&\ddots\\0&&\cdots&1\\\end{matrix}\right)_{2^k\times2^k}\otimes A=\left(\begin{matrix}A&0&\cdots&0\\0&A\\\vdots&&\ddots\\0&&\cdots&A\\\end{matrix}\right)_{2^kdim(A) \times 2^kdim(A)}$

即单位矩阵从左边与矩阵A直积，等效于在一个$2^kdim(A)\times 2^kdim(A)$的矩阵中，从$(0,0)$开始，沿着对角线的方向以$dim（A）$为周期平移$A$. 



在实际计算中，我们可以同时考虑$I$从左作用和从右作用的效果，两者是不矛盾的（独立的），借用固体物理的概念，打个比方，即$I$右直乘于$S_{XYbase}$得到了基元$A$，而$I$左直乘于$A$则是生成了点阵.

上述算法的时间复杂程度$O(L2^L)$，而直接直积的时间复杂程度是$O(L4^L)$,即利用$S$与$I$的特点来优化，在内存占用减少的同时(不是全部储存,而是采取类似字典的方式)可以获得$2^L$倍左右的加速.

*经实际测试,L=20的情况内存占用为135mb左右,计算耗时27.241465 s,最终共得到6291456个数据.*

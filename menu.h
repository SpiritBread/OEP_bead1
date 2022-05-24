#pragma once

#include <iostream>
#include "matrixn.h"
#include <vector>

class Menu
{
    public:
        Menu(){};
        void Run();
    private:
        int MenuPrint();
        void SetM1();
        void SetM2();
        void SumMatrix();
        void MulMatrix();
        void PrintMatrix1();
        void PrintMatrix2();
        void PrintM1elem();
        void PrintM2elem();
        //void EqualMatrixes(); // ezt majd torold ki
        Matrix m1;
        Matrix m2;
        Matrix result;
};


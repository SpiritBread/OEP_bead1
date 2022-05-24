#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class Matrix {
private:
    int n;
    bool parose;
    std::vector<int> vec;
public:
    Matrix(){
    n=4;
    parose=true;
    vec.resize(n*(n/2));
    }
    Matrix(int m){
        n=m;
        if (n%2==0){
            parose=true;
            vec.resize(n*(n/2));
        }else{
            parose=false;
            bool nulla=false;
            int szam=0;
            for (int i=0;i<(n*n);++i){
                if (!nulla){
                    szam++;
                    nulla=true;
                }else{
                    nulla=false;
                }
            }
            vec.resize(szam);
        }
        for (int i=0;i<vec.size();++i){
            vec[i]=2;   //kettesekkel toltjuk fel a matrixot
        }
    }

    enum Exception {OverIndexing,UnderIndexing,DimensionError};

    //getterek
    int getN() const {return n;}
    bool getP() const {return parose;}
    int getVecSize() const {return (vec.size());}
    int getVecElement(int i){return vec[i];}
    int getElement(int i,int j){
        if (i<0 || j<0){
            throw UnderIndexing;
        }
        if (i>n || j>n){
            throw OverIndexing;
        }
        if (i%2 != j%2){
            return 0;
        }
        if (parose){
            return vec[((i-1)*(n/2) + ((j-1)/2))];   //kihasznalom azt, hogy paratlan szam osztasa lefele kerekit
        }else{
            int index=0;
            for (int k=0;k<(i-1);++k){
                if (k%2 == 0){
                    index += (n/2+1);
                }else{
                    index += (n/2);
                }
            }
            return vec[index+((j-1)/2)];
        }
    }

    void getMatrix(){
        for (int i=0;i<n;++i){
            for (int j=0;j<n;++j){
                std::cout << getElement((i+1),(j+1)) << " ";
            }
            std::cout << std::endl;
        }
    }

    //setterek
    void setElement (int x,int i, int j){   //fejlesztoi eszkoz, nem a felhasznalonak van ezert 0-tol indexel nem 1-tol
        if (parose){
            vec[(i*(n/2) + (j/2))] = x;
        }else{
            int index=0;
            for (int k=0;k<i;++k){
                if (k%2 == 0){
                    index += (n/2+1);
                }else{
                    index += (n/2);
                }
            }
            vec[index+(j/2)] = x;
        }
    }

    void setMatrix(){
        std::cout << "Adja meg a matrix meretet: " << std::endl;
        std::cin >> n;
        while (n <= 0){
            std::cout << "0-nal nagyobb szamot adj meg!" << std::endl;
            std::cin >> n;
        }
        if (n%2==0){
            parose=true;
            vec.resize(n*(n/2));
        }else{
            parose=false;
            bool nulla=false;
            int szam=0;
            for (int i=0;i<(n*n);++i){
                if (!nulla){
                    szam++;
                    nulla=true;
                }else{
                    nulla=false;
                }
            }
            vec.resize(szam);
        }

        int bemenet;
        int index=0;
        if (parose){
            int oszlop;
            for (int i=0;i<(n);++i){
                if (i%2==0){
                    oszlop=(-1);
                }else{
                    oszlop=0;
                }
                for (int j=0;j<(n/2);++j){
                    oszlop +=2;
                    std::cout << "Kerem adja meg a(z) " << (i+1) << ". sor " << oszlop << ". elemet:" << std::endl;
                    std::cin >> bemenet;
                    vec[index]=bemenet;
                    index++;
                }
            }
        }else{
            int oszlop;
            for (int i=0;i<n;++i){
                if (i%2==0){
                    oszlop=(-1);
                    for (int j=0;j<(n/2+1);++j){
                        oszlop += 2;
                        std::cout << "Kerem adja meg a(z) " << (i+1) << ". sor " << oszlop << ". elemet:" << std::endl;
                        std::cin >> bemenet;
                        vec[index]=bemenet;
                        index++;
                    }
                }else{
                    oszlop=0;
                    for (int j=0;j<(n/2);++j){
                        oszlop += 2;
                        std::cout << "Kerem adja meg a(z) " << (i+1) << ". sor " << oszlop << ". elemet:" << std::endl;
                        std::cin >> bemenet;
                        vec[index]=bemenet;
                        index++;
                    }
                }
            }
        }
    }

    bool isEquals(Matrix a){
        if (a.getN() != n){
            return false;
        }
        for (int i=0;i<vec.size();++i){
            if ( vec[i] != a.getVecElement(i) ){
                return false;
            }
        }
        // ha eddig meg nem returnoltunk:
        return true;
    }

    void sumMatrix(Matrix a, Matrix b){
        if (a.getN() != b.getN()){
            throw DimensionError;
        }
        n=a.getN();
        parose=a.getP();
        vec.resize(a.getVecSize());

        for (int i=0;i<vec.size();++i){
            vec[i]= a.getVecElement(i) + b.getVecElement(i);
        }
    }

    void mulMatrix(Matrix a, Matrix b){
        if (a.getN() != b.getN()){
            throw DimensionError;
        }
        //ha nem throwoltunk akkor menjunk neki

        //result konstrualas
        n = a.getN();
        parose= a.getP();
        vec.resize(a.getVecSize());

        for (int i=0;i<vec.size();++i){
            vec[i]=0;
        }   //elmeletileg a resize-nak le kene nullaznia, de ha megegyszer lefuttatom a szorzast nem nullaz magatol, valszeg mert nem valtozik a meret



        bool prs=false;
        if (parose){
            prs=true;
        }
        int valtozo=0;
        for (int i=1;i<=n;++i){
            if (parose){
                prs = !prs;
            }
            for (int j=1;j<=n;++j){
                if (!prs){
                    for (int k=1;k<=n;++k){
                        if (i%2==k%2){
                            //std::cout <<"i,j: " << i  << " " << j << " a elem: " << a.getElement(i,j) << " b elem: " << b.getElement(j,i) <<std::endl;
                            vec[valtozo] += (a.getElement(i,k)* b.getElement(k,j));
                        }
                    }
                    valtozo++;
                }
                prs = !prs;
            }
        }
    }
};

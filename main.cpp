#include <iostream>
#include "menu.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main(){
	Menu m;
	m.Run();
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "matrixn.h"


TEST_CASE("getElement()"){
    SECTION("Nem-null elem lekerese"){
        Matrix a;
        int xd=69;
        a.setElement(xd,2,2);   //indexeles miatt eggyel kisebb mint a getelementes szamok
        CHECK( a.getElement(3,3) == xd );
    }

    SECTION("Null elem lekerese"){
        //kulcs: Ha i paros es j nem, vagy forditva, akkor mindig null elem lesz
        Matrix a = Matrix(4);  //a nem null elemek helyei kettesekkel vannak feltoltve
        CHECK ( a.getElement(1,2) == 0 );
        CHECK ( a.getElement(2,3) == 0 );
        CHECK ( a.getElement(2,2) == 2 );
        CHECK ( a.getElement(1,1) == 2 );
    }

}

TEST_CASE("sumMatrix()", "(isEquals())" ){


    SECTION("Null matrixok osszeadasa"){
        Matrix a;   // 4x4 null matrix
        Matrix b;   // 4x4 null matrix
        Matrix c;   // 4x4 null matrix
        Matrix result;  // 4x4 null matrix

        result.sumMatrix(a,b);

        CHECK( result.isEquals(c) );    //fo teszteset
        CHECK ( c.isEquals(b) );
        CHECK ( b.isEquals(a));
    }

    SECTION("Nem-null matrixok osszaadasa"){
        Matrix a;
        Matrix b;
        Matrix c;
        Matrix result;

        a.setElement(42,0,1);
        b.setElement(420,1,1);
        b.setElement(27,0,1);
        c.setElement(69,0,1);
        c.setElement(420,1,1);

        result.sumMatrix(a,b);

        CHECK( result.isEquals(c) );    //fo teszteset

        result.sumMatrix(a,c);
        CHECK( !result.isEquals(a) );
        CHECK( !result.isEquals(b) );
        CHECK( !result.isEquals(c) );

        Matrix d;

        result.sumMatrix(c,d);  //null matrix + nem-null matrix == maga a nem-null matrix
        CHECK( result.isEquals(c));
    }

    SECTION("Hibadobas"){
        Matrix a(4);
        Matrix b(5);
        Matrix result;

        CHECK_THROWS(result.sumMatrix(a,b));

        Matrix c(5);

        CHECK_NOTHROW(result.sumMatrix(c,b));
    }

}

TEST_CASE("mulMatrix()"){

    SECTION("Null matrixok szorzasa"){
        Matrix a;
        Matrix b;
        Matrix result;

        result.mulMatrix(a,b);

        CHECK(result.isEquals(a));
        CHECK(a.isEquals(b));
    }

    SECTION("Paros meretu matrixok szorzasa"){
        Matrix a(4);
        Matrix b(4);
        Matrix c(4);

        a.setElement(12,0,0);
        a.setElement(23,0,2);
        a.setElement(34,1,1);
        a.setElement(45,1,3);
        a.setElement(56,2,0);
        a.setElement(67,2,2);
        a.setElement(78,3,1);
        a.setElement(89,3,3);

        b.setElement(98,0,0);
        b.setElement(87,0,2);
        b.setElement(76,1,1);
        b.setElement(65,1,3);
        b.setElement(54,2,0);
        b.setElement(43,2,2);
        b.setElement(32,3,1);
        b.setElement(21,3,3);

        //https://matrix.reshish.com/multCalculation.php
        c.setElement(2418,0,0);
        c.setElement(2033,0,2);
        c.setElement(4024,1,1);
        c.setElement(3155,1,3);
        c.setElement(9106,2,0);
        c.setElement(7753,2,2);
        c.setElement(8776,3,1);
        c.setElement(6939,3,3);

        Matrix result;

        result.mulMatrix(a,b);

        CHECK(result.isEquals(c));
    }



    SECTION("Paratlan meretu matrixok szorzasa"){
        Matrix a(3);
        Matrix b(3);
        Matrix c(3);
        Matrix result;

        a.setElement(1,0,0);
        a.setElement(2,0,2);
        a.setElement(3,1,1);
        a.setElement(4,2,0);
        a.setElement(5,2,2);

        b.setElement(1,0,0);
        b.setElement(2,0,2);
        b.setElement(3,1,1);
        b.setElement(4,2,0);
        b.setElement(5,2,2);

        //https://matrix.reshish.com/multCalculation.php
        c.setElement(9,0,0);
        c.setElement(12,0,2);
        c.setElement(9,1,1);
        c.setElement(24,2,0);
        c.setElement(33,2,2);

        result.mulMatrix(a,b);

        CHECK(result.isEquals(c));


    }

    SECTION("Hibadobas"){
        Matrix a(3);
        Matrix b(5);
        Matrix result;

        CHECK_THROWS(result.mulMatrix(a,b));

        Matrix c(5);

        CHECK_NOTHROW(result.mulMatrix(b,c));
    }
}


#endif

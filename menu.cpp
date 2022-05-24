#include "menu.h"

using namespace std;


void Menu::Run(){
	int v;
	do{
		v=MenuPrint();
		switch(v)
		{
			case 1:
				SetM1();
				PrintMatrix1();
				break;
			case 2:
				SetM2();
				PrintMatrix2();
				break;
			case 3:
				SumMatrix();
				break;
			case 4:
				MulMatrix();
				break;
			case 5:
				PrintMatrix1();
				break;
            case 6:
				PrintMatrix2();
				break;
            case 7:
				PrintM1elem();
				break;
            case 8:
				PrintM2elem();
				break;
				/*
            case 9: //ezt majd torold ki
                EqualMatrixes();
                break;
                */
			default:
				cout<<"\nViszontlatasra!\n";
				break;
		}
	}while(v!=0);
}

int Menu::MenuPrint(){
	cout<<"\n****************************************\n";
	cout<<"0. Kilepes\n";
	cout<<"1. Elso matrix beallitasa\n";
	cout<<"2. Masodik matrix beallitasa\n";
	cout<<"3. Matrixok osszeadasa\n";
	cout<<"4. Matrixok szorzasa\n";
	cout<<"5. Elso matrix kiirasa\n";
	cout<<"6. Masodik matrix kiirasa\n";
	cout<<"7. Elso matrix megadott elemenek kiirasa\n";
	cout<<"8. Masodik matrix megadott elemenek kiirasa\n";
	cout<<"****************************************\n";

	int valasz;
	cin >> valasz;
	while (valasz < 0 || valasz > 8){
		cout << "0 es 8 kozti szamot adj meg!" << endl;
		cin >> valasz;
	}

	return valasz;
}


void Menu::SetM1(){
	m1.setMatrix();
}
void Menu::SetM2(){
	m2.setMatrix();
}

void Menu::SumMatrix(){
    try{
        result.sumMatrix(m1,m2);
        cout << "A ket matrix osszege:" << endl;
        result.getMatrix();
    }
    catch(Matrix::Exception){
        cout << "Ezt a ket matrixot nem lehet osszeadni, mert a dimenzioik nem egyeznek meg!" <<endl;
    }
}
void Menu::MulMatrix(){
    try{
        result.mulMatrix(m1,m2);
        cout << "A ket matrix szorzata:" << endl;
        result.getMatrix();
    }
    catch(Matrix::Exception e){
        cout << "Ezt a ket matrixot nem lehet osszeszorozni, mert a dimenzioik nem megfeleloek! (elso matrix masodik dimenzioja = masodik matrix elso dimenzioja)" <<endl;
    }
}
void Menu::PrintMatrix1(){
    cout << "Az elso matrixod:" << endl;
	m1.getMatrix();
}
void Menu::PrintMatrix2(){
    cout << "A masodik matrixod:" << endl;
	m2.getMatrix();
}
void Menu::PrintM1elem(){
    int i,j;
    cout << "Add meg a sor szamat: " <<endl;
    cin >> i;
    cout << "Add meg az oszlop szamat: " <<endl;
    cin >> j;
    int a;
    try{
        a = m1.getElement(i,j);
        cout << "Az elem: " << a <<endl;
    }
    catch(Matrix::Exception e){
        if (e==Matrix::OverIndexing){
            cout << "Tulindexeles! Kerlek legkozelebb ne adj meg nagyobb szamokat, mint a matrix meretei!" <<endl << "A matrixod:" <<endl;
            m1.getMatrix();
        }else if (e==Matrix::UnderIndexing){
            cout << "Ne adj meg 1-nel kisebb indexet!"<<endl;
        }
        else{
            cout << "Gratulalok! Olyan hibara futottal, amit el se lehet erni!" <<endl;
        }
    }
}
void Menu::PrintM2elem(){
    int i,j;
    cout << "Add meg a sor szamat: " <<endl;
    cin >> i;
    cout << "Add meg az oszlop szamat: " <<endl;
    cin >> j;
    int a;
    try{
        a = m2.getElement(i,j);
        cout << "Az elem: " << a <<endl;
    }
    catch(Matrix::Exception e){
        if (e==Matrix::OverIndexing){
            cout << "Tulindexeles! Kerlek legkozelebb ne adj meg nagyobb szamokat, mint a matrix meretei!" <<endl << "A matrixod:" <<endl;
            m2.getMatrix();
        }else if (e==Matrix::UnderIndexing){
            cout << "Ne adj meg 1-nel kisebb indexet!"<<endl;
        }
        else{
            cout << "Gratulalok! Olyan hibara futottal, amit el se lehet erni!" <<endl;
        }
    }
}
/*
void Menu::EqualMatrixes(){
    bool a= m1.isEquals(m2);
    if (a){
        cout << "Egyenlo <3" << endl;
    }else{
        cout << "A ket matrix kozott egyenlotlenseg all fent, valoszinuleg azert, mert nem egyenloek." <<endl;
    }
}
*/

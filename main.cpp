#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

//---Deklaracje zmiennych globalnych--------

double k1=0, k2=0, Ft=0;
FILE *fp;
char nazwa_pliku[128];

//---Funkcja signum zwracaj¹ca znak wprowadzonego x--------
double sign(double x)
{
	if(x<0) 
		{ return -1;} 
	else if(x>0) 
		{ return 1; } 
	else 
		{ return 0; }
	
}

//---Funkcje liczace pochodne------------------------------
double px1 (double t, double x1, double x2)
{
	return x2;								//bo x2 = x1', czyli x2 = (dx1/dt)
}
double px2 (double t, double x1, double x2)
{
	return (Ft-k1 * sign(x2) * x2*x2 - k2 * x1); //bo x2' = -k1*sign(x2)*x2^2-k2*x1
}
//---------------------------------------------------------


int main(int argc, char** argv) 
{
	double t, t0=0, tkon, x1, x2, h, a1,a2,a3,a4;
	int L,i,N;
	
	cout << "METODY NUMERYCZNE W INZYNIERII \n- Jan Jedrzejak - Weronika Rachwalska - Dominik Szczap - \n-------------------------------------------\nProgram numerycznie obliczajacy rownanie ruchu masy drgajacej\nMetoda RK-IV";
	cout << "\n\n\n";
	
	cout << "Wprowadz wspolczynnik k1: "; 					cin >> k1;
	cout << "Wprowadz wspolczynnik k2: "; 					cin >> k2;
	cout << "WprowadŸ sile dzialajaca na uklad F(t): ";     cin >> Ft;
	cout << "Czas kon: "; 				  					cin >> tkon;
	cout << "Krok obliczenia: ";          					cin >> h;
	cout << "Krok wydruku (wielokrotnosc h): ";             cin >> N;
	cout << "Nazwa pliku wynikowego: ";						scanf("%s", &nazwa_pliku);
	strcat(nazwa_pliku, ".csv");
	
	//-------dzialania na pliku---------------------
	if ((fp=fopen(nazwa_pliku, "w"))==NULL)
	{
		cout << "Otwarcie pliku niemozliwe!\n";
		exit;
	} else {
		cout << "Plik poprawnie otwarty...\n";
	}
	//----------------------------------------------
	
	cout << "\nCzas t: | Rozwiazanie numeryczne: \n";
	cout << "-------------------------------------\n";
	
	x1=0; x2=10; t=t0; L=0; i=0; //Inicjalizacja danych wejsciowych
	
	while (t<tkon)
	{
		a1=h*px1(t, x1, x2);
		a2=h*px1(t, x1+a1/2, x2);
		a3=h*px1(t, x1+a2/2, x2);
		a4=h*px1(t, x1+a3, x2);
		
		x1=x1+(a1+2*a2+2*a3+a4)/6;
		
		a1=h*px2(t, x1, x2);
		a2=h*px2(t, x1, x2+a1/2);
		a3=h*px2(t, x1, x2+a2/2);
		a4=h*px2(t, x1, x2+a3);
		
		x2=x2+(a1+2*a2+2*a3+a4)/6;
		
		if (++i == N)
			{
				printf(" %5.3f %15.3f\n %15.3f\n", t+h, x1, x2);
				//fprintf(fp, " %5.3f %15.3f %15.3f\n", t+h, x1, x2); //zapis do zwyklego pliku
				fprintf(fp, " %5.3f;%15.3f;%15.3f\n", t+h, x1, x2); //zapis do formatu csv
				i=0;
			}
			t=t0+(++L)*h;
	}
	cout << "Po otwarciu wynikowego pliku csv pamietaj, aby zamienic kropke na przecinek \n";
	
	fclose(fp);
	return 0;
}

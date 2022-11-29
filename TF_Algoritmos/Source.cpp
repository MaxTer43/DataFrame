//#include "ArbolAVLString.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <String>
#include <conio.h>
#include <vector>
//#include "Dataframe.h"
//#include "ArbolAVL_.h"
#include "ArbolAVLnew.h"
#include "ArbolAVLold.h"

using namespace std;

void data() {
	system("CLS");
	//	CArbolAVL* arbolAVLnombre = new CArbolAVL;

	vector <string> a;

	ArbolAVL<string>* t = new ArbolAVL<string>;

	CArbolAVL<string>* region = new CArbolAVL<string>;
	CArbolAVL<string>* country = new CArbolAVL<string>;
	CArbolAVL<string>* itemtype = new CArbolAVL<string>;
	CArbolAVL<string>* saleschannel = new CArbolAVL<string>;
	CArbolAVL<string>* orderpriority = new CArbolAVL<string>;
	CArbolAVL<string>* orderdate = new CArbolAVL<string>;
	CArbolAVL<string>* orderid = new CArbolAVL<string>;
	CArbolAVL<string>* shipdate = new CArbolAVL<string>;
	CArbolAVL<string>* unitssold = new CArbolAVL<string>;
	CArbolAVL<string>* unitprice = new CArbolAVL<string>;
	CArbolAVL<string>* unitcost = new CArbolAVL<string>;
	CArbolAVL<string>* totalrevenue = new CArbolAVL<string>;
	CArbolAVL<string>* totalcost = new CArbolAVL<string>;
	CArbolAVL<string>* totalprofit = new CArbolAVL<string>;

	ifstream ifile("1000 Sales Records.csv");

	string nombre, sexo;
	int edad;

	string Region, Country, ItemType, SalesChannel, OrderPriority, OrderDate, OrderID, ShipDate, UnitsSold, UnitPrice, UnitCost, TotalRevenue, TotalCost, TotalProfit;

	int linea = 0;
	string line; //Leer toda la linea
	while (getline(ifile, line)) // Leer la linea actual
	{
		istringstream iss{ line }; // Construir un string de la linea

		//Leer los tokens de la linea actual separada por coma

		vector<string> tokens; // Vector para almacenar tokens
		string token; // Token actual
		while (getline(iss, token, ','))
		{
			tokens.push_back(token); // Agregar token al vector
		}

		if (linea > 0) {
			Region = tokens[0];
			Country = tokens[1];
			ItemType = tokens[2];
			SalesChannel = tokens[3];
			OrderPriority = tokens[4];
			OrderDate = tokens[5];
			OrderID = tokens[6];
			ShipDate = tokens[7];
			UnitsSold = tokens[8];
			UnitPrice = tokens[9];
			UnitCost = tokens[10];
			TotalRevenue = tokens[11];
			TotalCost = tokens[12];
			TotalProfit = tokens[13];

			region->insertar(to_string(linea) + "-" + tokens[0]);
			country->insertar(to_string(linea) + "-" + tokens[1]);
			itemtype->insertar(tokens[2]);
			saleschannel->insertar(tokens[3]);
			orderpriority->insertar(tokens[4]);
			orderdate->insertar(tokens[5]);
			orderid->insertar(tokens[6]);
			shipdate->insertar(tokens[7]);
			unitssold->insertar(tokens[8]);
			unitprice->insertar(tokens[9]);
			unitcost->insertar(tokens[10]);
			totalrevenue->insertar(tokens[11]);
			totalcost->insertar(tokens[12]);
			totalprofit->insertar(tokens[13]);
		}

		a.push_back(tokens[0] + "," + tokens[1] + tokens[2] + "," + tokens[3] + "," + tokens[4] + "," + tokens[5] + "," + tokens[6] + "," + tokens[7] + "," + tokens[8] + "," + tokens[9] + "," + tokens[10] + "," + tokens[11] + "," + tokens[12] + "," + tokens[13]);

		if (linea > 0)
			t->insertar(a[linea]);

		linea += 1;
	}
		while (1) {
			int N;
			system("CLS");
			cout << "1- Orden de menor a mayor" << endl;
			cout << "2- Orden de mayor a menor" << endl;
			cout << "3- Variables mayores" << endl;
			cout << "4- Variables menores" << endl;
			cout << "5- Salir" << endl;
			cout << "6- Iniciar con primeras letras" << endl;
			cout << "7- Terminar con ultimas letras" << endl;
			cout << "8- Exportar archivo" << endl;
			cout << "9- Doble filtro" << endl;
			cout << "10 - NO inicia con primeras letras" << endl;
			cin >> N;
			if (N == 1)
			{
				t->mostrar(EnOrden2);
			}
			else if (N == 2)
			{
				t->mostrar(EnOrdenInverso2);
			}
			else if (N == 3) {
				cout << "Ingresa variable";
				string J;
				cin >> J;
				cout << a[0] << endl;
				t->mayor(J);
			}
			else if (N == 4) {
				cout << "Ingresa variable";
				string J;
				cin >> J;
				cout << a[0] << endl;
				t->menor(J);
			}
			else if (N == 5)
				exit(0);
			else if (N == 6)
			{
				cout << "Ingresa variable";
				string J;
				cin >> J;
				cout << a[0] << endl;
				t->empezarCon(J);
			}
			else if (N == 7)
			{
				cout << "Ingresa variable";
				string J;
				cin >> J;
				cout << a[0] << endl;
				t->terminarCon(J);
			}
			else if (N == 8)
			{
				ofstream myfile("Resultado.txt");
				if (myfile.is_open())
				{
					for (int i = 0; i < a.size(); i++) {
						if (i == a.size() - 1)
							myfile << a[i];
						else
							myfile << a[i] << "\n";
					}
					myfile.close();
				}
				cout << "Exportado.";
			}
			else if (N == 9)
			{

			}
			else if (N == 10)
			{
				cout << "Ingresa variable";
				string J;
				cin >> J;
				cout << a[0] << endl;
				t->NOempezarCon(J);
			}
			cout << endl;
			cout << "Presiona enter para volver";
			_getch();
		}
	}
void main()
{
	while (1)
	{
		system("CLS");
		int N;
		cout << "Dataframe" << endl;
		cout << "1- Cargar dataframe" << endl;
		cout << "2- Salir" << endl;
		cin >> N;
		if (N == 1) {
			data();
		}
		else if (N == 2) {
			exit(0);
		}
	}

	_getch();
}

#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

enum Recorrido { EnOrden, EnOrdenEdad, EnOrdenInverso, PreOrden, PostOrden, Especifico, Mayor, Menor };

template<typename T>
class CArbolAVL {
	struct Nodo
	{
		T valor;
		T indice;
		struct Nodo* hizq;
		struct Nodo* hder;
		int altura;
		Nodo(T valor, Nodo* hizq = nullptr, Nodo* hder = nullptr, int altura = 1)
			: valor(valor), hizq(hizq), hder(hder), altura(altura) {}
	};
	Nodo* raiz;
public:
	CArbolAVL() : raiz(nullptr) { }
	~CArbolAVL() {

	}
	void insertar(T valor) {
		this->raiz = insertar(raiz, valor);
	}
	void borrar(T valor) {
		this->raiz = borrar(raiz, valor);
	}
	void buscar(T valor) {
		this->raiz = buscar(raiz, valor);
	}
	void mayor(T valor) {
		this->raiz = mayor(raiz, valor);
	}
	void menor(T valor) {
		this->raiz = mayor(raiz, valor);
	}
	void empezarCon(T valor) {
		this->raiz = empezarCon(raiz, valor);
	}
	void terminarCon(T valor) {
		this->raiz = terminarCon(raiz, valor);
	}
	void mostrar(Recorrido recorrido) {
		switch (recorrido) {
		case EnOrden: enOrden(raiz); break;
		case EnOrdenInverso: enOrdenInverso(raiz); break;
		case PreOrden: preOrden(raiz); break;
		case PostOrden: postOrden(raiz); break;
			//		case Mayor: mayor(raiz, valor); break;

		}
	}
private:
	Nodo* insertar(Nodo* nodo, T valor)
	{
		// 1. Realizar la inserción
		if (nodo == nullptr)
			return new Nodo(valor);
		if (valor < nodo->valor)
			nodo->hizq = insertar(nodo->hizq, valor);
		else if (valor > nodo->valor)
			nodo->hder = insertar(nodo->hder, valor);
		else // No admite nodos duplicados
			return nodo;

		/* 2. Actualiza la altura del padre del nodo ingresado*/
		nodo->altura = 1 + max(altura(nodo->hizq), altura(nodo->hder));

		/* 3. Obtiene el factor de balance del nodo padre para saber si está desbalanceado */
		int balance = obtenerBalance(nodo);

		// Si el nodo está desbalanceado entonces podemos solucionarlo de 4 formas

		// Caso Izquierda Izquierda
		if (balance > 1 && valor < nodo->hizq->valor)
			return rotarDerecha(nodo);

		// Caso Derecha Derecha
		if (balance < -1 && valor > nodo->hder->valor)
			return rotarIzquierda(nodo);

		// Caso Izquierda Derecha
		if (balance > 1 && valor > nodo->hizq->valor)
		{
			nodo->hizq = rotarIzquierda(nodo->hizq);
			return rotarDerecha(nodo);
		}

		// Caso Derecha Izquierda
		if (balance < -1 && valor < nodo->hder->valor)
		{
			nodo->hder = rotarDerecha(nodo->hder);
			return rotarIzquierda(nodo);
		}

		// Retorna el puntero a la raiz del árbol balanceado
		return nodo;
	}

	Nodo* borrar(Nodo* nodo, T valor)
	{
		// 1: Realizar "Eliminación" de BST
		if (nodo == NULL)
			return nodo;

		// Si el valor a ser borrado es menor que el valor de la raiz,
		// entonces continuamos por el hijo de la izquierda
		if (valor < nodo->valor)
			nodo->hizq = borrar(nodo->hizq, valor);

		// Si el valor a ser borrado es mayor que el valor de la raiz,
		// entonces continuamos por el hijo de la derecha
		else if (valor > nodo->valor)
			nodo->hder = borrar(nodo->hder, valor);

		// Si el valor es el mismo que el de la raiz, 
		// entonces es el nodo a ser borrado
		else
		{
			// nodo con un o ningún hijo
			if ((nodo->hizq == NULL) || (nodo->hder == NULL))
			{
				Nodo* temp = nodo->hizq ? nodo->hizq : nodo->hder;

				// Sin hijos
				if (temp == NULL)
				{
					temp = nodo;
					nodo = NULL;
				}
				else // Con un hijo 
					*nodo = *temp; // Copiamos el valor del nodo hijo
				delete temp;
			}
			else
			{
				// Nodo con 2 hijos: toma el menor hijo del hijo de la derecha
				Nodo* temp = hallarMenorSucesor(nodo->hder);

				// Copia el valor del menor sucesor al nodo actual
				nodo->valor = temp->valor;

				// Borra el espacio ocupado por el scesor
				nodo->hder = borrar(nodo->hder, temp->valor);
			}
		}

		// Si el árbol sólo tiene un nodo a retornar
		if (nodo == NULL)
			return nodo;

		// 2. Actualizar la altura del nodo actual
		nodo->altura = 1 + max(altura(nodo->hizq), altura(nodo->hder));

		// 3. Obtener el factor de balance del nodo (para verificar si el nodo está desbalanceado) 
		int balance = obtenerBalance(nodo);

		// Si es que está desbalanceado entonces hay 4 casos

		// Caso Izquierda Izquierda
		if (balance > 1 && obtenerBalance(nodo->hizq) >= 0)
			return rotarDerecha(nodo);

		// Caso Izquierda Derecha
		if (balance > 1 && obtenerBalance(nodo->hizq) < 0)
		{
			nodo->hizq = rotarIzquierda(nodo->hizq);
			return rotarDerecha(nodo);
		}

		// Caso Derecha Derecha
		if (balance < -1 && obtenerBalance(nodo->hder) <= 0)
			return rotarIzquierda(nodo);

		// Caso Derecha Izquierda
		if (balance < -1 && obtenerBalance(nodo->hder) > 0)
		{
			nodo->hder = rotarDerecha(nodo->hder);
			return rotarIzquierda(nodo);
		}

		return nodo;
	}

	Nodo* buscar(Nodo* nodo, T valor)
	{
		if (nodo != NULL)
		{
			if (valor < nodo->valor)
				nodo->hizq = buscar(nodo->hizq, valor);

			// Si el valor a ser borrado es mayor que el valor de la raiz,
			// entonces continuamos por el hijo de la derecha
			else if (valor > nodo->valor)
				nodo->hder = buscar(nodo->hder, valor);

			// Si el valor es el mismo que el de la raiz, 
			// entonces el nodo existe
			else if (valor == nodo->valor)
			{
				cout << nodo->valor;
			}
		}
		/*
		if (nodo != NULL)
		{
			mayor(raiz->hizq, valor);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;

			if (valor == raiz->valor)
				cout << raiz->valor << endl;
			mayor(raiz->hder, valor);
		}
		*/
		return nodo;
	}

	Nodo* mayor(Nodo* raiz, T valor)
	{
		if (raiz != NULL)
		{
			mayor(raiz->hizq, valor);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;

			if (valor < raiz->valor)
				cout << raiz->valor;
			mayor(raiz->hder, valor);
		}
		return raiz;
	}
	Nodo* menor(Nodo* raiz, T valor)
	{
		if (raiz != NULL)
		{
			mayor(raiz->hizq, valor);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;

			if (valor > raiz->valor)
				cout << raiz->valor;
			mayor(raiz->hder, valor);
		}
		return raiz;
	}
	Nodo* empezarCon(Nodo* raiz, T valor)
	{
		if (raiz != NULL)
		{
			empezarCon(raiz->hizq, valor);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;

			if (raiz->valor.rfind(valor, 0) == 0) {
				cout << raiz->valor;
			}
			empezarCon(raiz->hder, valor);
		}
		return raiz;
	}

	Nodo* terminarCon(Nodo* raiz, T valor)
	{
		if (raiz != NULL)
		{
			terminarCon(raiz->hizq, valor);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;
			/*
			if (raiz->valor.rfind(valor, 0) == 0) {
				cout << raiz->valor << endl;
			}
			*/
			if (raiz->valor.size() >= valor.size() &&
				raiz->valor.compare(raiz->valor.size() - valor.size(), valor.size(), valor) == 0)
				cout << raiz->valor << endl;

			terminarCon(raiz->hder, valor);
		}
		return raiz;
	}

	void enOrden(struct Nodo* raiz)
	{
		ofstream file;
		file.open("auxiliar.txt");


		if (raiz != NULL)
		{
			enOrden(raiz->hizq);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;
			cout << raiz->valor;
			enOrden(raiz->hder);
		}
	}

	void enOrdenInverso(struct Nodo* raiz)
	{
		if (raiz != NULL)
		{
			enOrdenInverso(raiz->hder);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;
			cout << raiz->valor;
			enOrdenInverso(raiz->hizq);
		}
	}

	void preOrden(struct Nodo* raiz)
	{
		if (raiz != NULL)
		{
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;
			cout << raiz->valor;
			enOrden(raiz->hizq);
			enOrden(raiz->hder);
		}
	}
	void postOrden(struct Nodo* raiz)
	{
		if (raiz != NULL)
		{
			enOrden(raiz->hizq);
			enOrden(raiz->hder);
			//cout << raiz->valor << " (" << raiz->altura << ") " << endl;
			cout << raiz->valor;
		}
	}
	inline int altura(struct Nodo* N) { return N ? N->altura : 0; }
	inline int max(int a, int b) { return (a > b) ? a : b; }
	inline int obtenerBalance(Nodo* N) { return N ? (altura(N->hizq) - altura(N->hder)) : 0; }
	Nodo* rotarDerecha(Nodo* y)
	{
		Nodo* x = y->hizq;
		Nodo* T2 = x->hder;

		// Rotando
		x->hder = y;
		y->hizq = T2;

		// Actualizando alturas
		y->altura = max(altura(y->hizq), altura(y->hder)) + 1;
		x->altura = max(altura(x->hizq), altura(x->hder)) + 1;

		// Retornando la nueva raiz
		return x;
	}
	Nodo* rotarIzquierda(Nodo* x)
	{
		Nodo* y = x->hder;
		Nodo* T2 = y->hizq;

		// Rotando
		y->hizq = x;
		x->hder = T2;

		// Actualizando alturas
		x->altura = max(altura(x->hizq), altura(x->hder)) + 1;
		y->altura = max(altura(y->hizq), altura(y->hder)) + 1;

		// Retornando la nueva raiz
		return y;
	}
	Nodo* hallarMenorSucesor(Nodo* nodo)
	{
		Nodo* actual = nodo;
		//Bucle para encontrar el nodo mas a la izquierda
		while (actual->hizq != NULL)
			actual = actual->hizq;
		return actual;
	}
};
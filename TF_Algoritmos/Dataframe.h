#pragma once
#include <String>
#include <vector>
#include "ArbolAVL.h"
#include <sstream>
#include <fstream>

class Dataframe {
	private:
		string nombre;
		
	public:

		Dataframe(string nombre) {
			nombre = nombre;
		}

		string getNombre() {
			return nombre;
		}

		void setNombre(string nombre) {
			nombre = nombre;
		}
};

/*
class DataFrame {
public:
	explicit
		DataFrame(int fila)
		: m_fila(fila)
	{}
	int fila() const {
		return m_fila;
	}

private:
	int m_fila;
};
*/
/*
class NombreDataFrame : public DataFrame {
public:
	NombreDataFrame(int fila, int numberOfCol)
		: DataFrame(fila), m_numberOfcol(numberOfcol)
	{}
	int NumberOfCol() const {
		return m_numberOfCol;
	}

private:
	int m_numberOfWheels;
};

class EdadedLandDataFrame : public DataFrame {
public:
	EdadDataFrame(int fila, int numberOfEdad)
		: DataFrame(fila), m_numberOfEdad(numberOfEdad)
	{}
	int NumberOfEdad() const {
		return m_numberOfEdad;
	}

private:
	int m_numberOfEdad;
};
*/
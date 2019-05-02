#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include <iostream>
#include <iomanip>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

class Articulo{
	public:
		Articulo(const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned stock);
		Cadena referencia()const;
		Cadena titulo()const;
		Fecha f_publi()const;
		double precio()const;
		double& precio();
		unsigned stock()const;
		unsigned& stock();
	private:
		Cadena refer, titul;
		Fecha fech_p;
		double valor;
		unsigned existencias;
};

ostream& operator<<(ostream& os, const Articulo& art);

#endif
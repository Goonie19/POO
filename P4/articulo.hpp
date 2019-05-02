#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include <iostream>
#include <iomanip>
#include "fecha.hpp"
#include "cadena.hpp"
#include <set>

using namespace std;

class Autor{
	public:
		Autor(const Cadena& nom, const Cadena& apell, const Cadena& dir);
		const Cadena& nombre()const noexcept;
		const Cadena& apellidos()const noexcept;
		const Cadena& direccion()const noexcept;
	private:
		Cadena nom_, apell_, dir_;
};

class Articulo{
	public:
		typedef set<Autor*> Autores;
		class Autores_vacios{};
		Articulo(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec);
		const Autores& autores()const;
		const Cadena& referencia()const;
		const Cadena& titulo()const;
		const Fecha& f_publi()const;
		double precio()const;
		double& precio();
		virtual void impresion_especifica(ostream& os)const=0;
		virtual ~Articulo(){}
	protected:
		Autores aut;
		Cadena refer;
		Cadena titul;
		Fecha fech_p;
		double valor;
};

ostream& operator<<(ostream& os, const Articulo& art);

class ArticuloAlmacenable: public Articulo{
	public:
		ArticuloAlmacenable(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned stock=0);
		unsigned stock()const;
		unsigned& stock();
	protected:
		unsigned stock_;
};
class LibroDigital: public Articulo{
	public:
		LibroDigital(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, const Fecha& fExpir);
		const Fecha& f_expir()const;
		void impresion_especifica(ostream& os)const;
	private:
		const Fecha f_expir_;

};

class Libro: public ArticuloAlmacenable{
	public:
		Libro(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned n_pags, unsigned stock=0);
		unsigned n_pag()const;
		void impresion_especifica(ostream& os)const;
	private:
		unsigned n_pag_;
};

class Cederron:public ArticuloAlmacenable{
	public:
		Cederron(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned tam, unsigned stock=0);
		unsigned tam()const;
		void impresion_especifica(ostream& os)const;
	private:
		unsigned tam_;
};

#endif
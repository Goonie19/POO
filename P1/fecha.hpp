#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <chrono>
#include <cstdio>

using namespace std;

class Fecha{
	public:
		static const int AnnoMaximo=2037;
		static const int AnnoMinimo=1902;
		Fecha& operator+=(const int n);
		Fecha& operator-=(const int n);
		Fecha& operator++();
		Fecha& operator--();
		Fecha operator++(int);
		Fecha operator--(int);
		Fecha operator+(int n)const;
		Fecha operator-(int n)const;
		const char * cadena()const;// metodo de la clase para convertir la fecha a cadena
		//constructores
		explicit Fecha(int dia=0, int mes=0, int anno=0);
		Fecha(const char * cadena);
		//metodos observadores
		int anno()const{return a;}
		int mes()const{return m;}
		int dia()const noexcept{return d;}
		//clase invalida para las excepciones
		class Invalida{
				const char* razon;
			public:
				Invalida(const char* razon);
				const char* por_que()const;
		};
	private:
		int d, m, a;//enteros para representar el dia, mes y año
		void validaFecha(int dia, int mes, int anno);//metodo para comprobar si la fecha introducida es correcta
};
	ostream& operator<<(ostream& os, const Fecha& f);
	istream& operator>>(istream& is, Fecha& f);
	bool operator<(const Fecha& t, const Fecha& f);
	bool operator>(const Fecha& t, const Fecha& f);
	bool operator==(const Fecha& t, const Fecha& f);
	bool operator!=(const Fecha& t, const Fecha& f);
	bool operator<=(const Fecha& t, const Fecha& f);
	bool operator>=(const Fecha& t, const Fecha& f);
#endif

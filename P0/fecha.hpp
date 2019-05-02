#ifndef FECHA_HPP
#define FECHA_HPP

#include <cstdlib>
#include <chrono>

class Fecha{
	public:
		Fecha& operator+=(const int n);
		Fecha& operator-=(const int n);
		Fecha& operator++();
		Fecha& operator--();
		Fecha& operator++(const int n=1);
		Fecha& operator--(const int n=1);
		Fecha& operator+(const int);
		Fecha& operator-(const int);
		operator const char*();
		//constructores
		explicit Fecha(int dia=0, int mes=0, int anno=0);
		Fecha(const Fecha& F);
		Fecha(const char * cadena);
		//metodos observadores
		int anno()const;
		int mes()const;
		int dia()const;
		//clase invalida para las excepciones
		class Invalida{
				const char* razon;
			public:
				Invalida(const char* razon);
				const char* por_que()const;
		};
	private:
		int d, m, a;//enteros para representar el dia, mes y año
		const char * cadena();//metodo que devuelve la cadena con la fecha
		static const int AnnoMaximo=2037;
		static const int AnnoMinimo=1902;
		void validaFecha(int dia, int mes, int anno);//metodo para comprobar si la fecha introducida es correcta
};
		bool operator<(const Fecha& t, const Fecha& f);
		bool operator>(const Fecha& t, const Fecha& f);
		bool operator==(const Fecha& t, const Fecha& f);
		bool operator<=(const Fecha& t, const Fecha& f);
		bool operator>=(const Fecha& t, const Fecha& f);

#endif
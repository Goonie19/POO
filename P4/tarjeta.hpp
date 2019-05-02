#ifndef TARJETA_HPP
#define TARJETA_HPP
#include "cadena.hpp"
#include <cstdlib>
#include <functional>
#include <algorithm>
#include "fecha.hpp"
#include "usuario.hpp"

using namespace std;

struct EsDigito{
	typedef char argument_type;
	bool operator()(char c)const{
		if(c>='0' && c<='9'){
			return true;
		}else{
			return false;
		}
	}
};

class Numero{
	public:
		enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
		class Incorrecto{
			public:
				Incorrecto(Razon raz);
				Razon razon()const;
			private:
				Razon raz;
		};
		Numero(const Cadena& num);
		operator const char*()const;
		friend bool operator<(const Numero& num, const Numero& num2);
	private:
		Cadena num_;
};

class Usuario;

class Tarjeta{
	public:
		enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};
		class Caducada{
			public:
				Caducada(const Fecha& caduc);
				const Fecha& cuando()const;
			private:
				Fecha fech_cad;
		};
		//constructores
		Tarjeta(Tipo t, const Numero& num_, Usuario& us, const Fecha& caducidad);
		Tarjeta(const Tarjeta& t)=delete;
		Tarjeta& operator=(const Tarjeta& t)=delete;
		//metodos observadores
		Tipo tipo()const{return tarjet;}
		Numero numero()const{return num_;}
		const Usuario* titular()const{return user;}
		Fecha caducidad()const{return caduci;}
		Cadena titular_facial()const{return tit_fac;}
		//metodos
		void anula_titular();
		~Tarjeta();
	private:
		Tipo tarjet;
		Numero num_;
		Usuario* user;
		Fecha caduci;
		Cadena tit_fac;

};
bool operator<(const Numero& num, const Numero& num2);
bool operator<(const Tarjeta& t, const Tarjeta& t2);
ostream& operator<<(ostream& os, const Tarjeta::Tipo& tipo);
ostream& operator<<(ostream& os, const Tarjeta& tar);

#endif

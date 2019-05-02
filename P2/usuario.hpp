#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <iostream>
#include <random>
#include <unistd.h>
#include <chrono>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "tarjeta.hpp"
#include "cadena.hpp"
#include "articulo.hpp"

using namespace std;

class Clave{
	public:
		//tipos de error
		enum Razon{CORTA, ERROR_CRYPT};
		//clase incorrecta
		class Incorrecta{
			Razon raz;
			public:
				Incorrecta(Razon cad);
				Razon razon()const;
		};
		//constructores
		Clave(const char * clave);
		//metodos observadores
		const Cadena& clave()const;
		bool verifica(const char *)const;
	private:
		Cadena pass;
};

class Numero;

class Tarjeta;

class Usuario{
	public:
		typedef map<Numero, Tarjeta*> Tarjetas;
		typedef unordered_map<Articulo*, unsigned> Articulos;
		typedef unordered_set<Cadena> Usuarios;
		Usuario(const Cadena& id, const Cadena& nombre, const Cadena& appellido, const Cadena& direccion, const Clave& clav);
		Usuario(const Usuario& user)=delete;
		Usuario& operator=(const Usuario& user)=delete;
		void es_titular_de(const Tarjeta& tarj);
		void no_es_titular_de(Tarjeta& tarj);
		Cadena id()const;
		Cadena nombre()const;
		Cadena apellidos()const;
		Cadena direccion()const;
		const Tarjetas& tarjetas()const;
		void compra(const Articulo& art, unsigned pedido=1);
		const Articulos& compra()const;
		size_t n_articulos()const;
		~Usuario();
		class Id_duplicado{//Clase para excepciones
			public:
				Id_duplicado(const Cadena& id_repe);
				const Cadena& idd()const;
			private:
				Cadena id_rep;
		};
		friend ostream& operator<<(ostream& os, const Usuario& user);
	private:
		static Usuarios list_user;
		Tarjetas list_tarj;
		Articulos list_art;
		//atributos
		Cadena id_user, name, apell, user_dir;
		Clave pass_;

};

void mostrar_carro(ostream& os, const Usuario& user);

#endif
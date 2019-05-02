#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
	public:
		Pedido(Usuario_Pedido& us_ped, Pedido_Articulo& ped_art, Usuario& us, const Tarjeta& tar, Fecha f=Fecha());
		int numero()const;
		const Tarjeta* tarjeta()const;
		Fecha fecha()const;
		double total()const;
		static int n_total_pedidos();
		class Vacio{
			public:
				Vacio(const Usuario& user);
				const Usuario& usuario()const{return us;}
			private:
				const Usuario& us;
		};
		class Impostor{
			public:
				Impostor(const Usuario& user);
				const Usuario& usuario()const{return imp_;}
			private:
				const Usuario& imp_;
		};
		class SinStock{
			public:
				SinStock(const Articulo* art);
				const Articulo& articulo()const{return *art_;}
			private:
				const Articulo* art_;
		};
	private:
		int num_;
		static int N_pedidos;
		const Tarjeta* tarjeta_;
		Fecha fecha_;
		double total_;

		void VaciaCarrito(Usuario& user);
};

ostream& operator<<(ostream& os, const Pedido& ped);

#endif
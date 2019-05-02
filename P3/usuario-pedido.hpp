#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP
#include "pedido.hpp"
#include <map>
#include <set>

class Usuario_Pedido{
	public:
		typedef set<Pedido*> Pedidos;
		void asocia(Usuario& user, Pedido& ped){as_usuario_pedido[&user].insert(&ped);}
		void asocia(Pedido& ped, Usuario& user){as_pedido_usuario[&ped]=&user;}
		Pedidos pedidos(Usuario& user)const{return as_usuario_pedido.at(&user);}
		Usuario* cliente(Pedido& ped)const{return as_pedido_usuario.at(&ped);}
	private:
		map<Usuario* , Pedidos> as_usuario_pedido;
		map<Pedido*, Usuario*> as_pedido_usuario;
};

#endif
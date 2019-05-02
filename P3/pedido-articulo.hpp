#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP
#include "pedido.hpp"


class LineaPedido{
	public:
		explicit LineaPedido(double pv, unsigned cant=1);
		const double precio_venta()const;
		const unsigned cantidad()const;
	private:
		double p_venta;
		unsigned cantidad_;
};

ostream& operator<<(ostream& os, const LineaPedido& l);

struct OrdenaPedidos{
	typedef Pedido* argument_type;
	bool operator()(Pedido* p1, Pedido* p2)const{
		return (p1->numero()<p2->numero());
	}
};

struct OrdenaArticulos{
	typedef Articulo* argument_type;
	bool operator()(Articulo* art, Articulo* art2)const{
		return (art->referencia()<art2->referencia());
	}
};

class Pedido_Articulo{
	public:
		typedef map<Articulo*,LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
		void pedir(Pedido& ped, Articulo& art, double precio, unsigned cant=1);
		void pedir(Articulo& art, Pedido& ped, double precio, unsigned cant=1);
		const ItemsPedido& detalle(Pedido& ped)const;
		Pedidos ventas(Articulo& art);
		ostream& mostrarDetallePedidos(ostream& os);
		ostream& mostrarVentasArticulos(ostream& os);
	private:
		map<Pedido*, ItemsPedido, OrdenaPedidos> as_pedido_artic;
		map<Articulo*, Pedidos, OrdenaArticulos> as_articulo_ped;
};

ostream& operator<<(ostream& os, const Pedido_Articulo::ItemsPedido& it);
ostream& operator<<(ostream& os, const Pedido_Articulo::Pedidos& ped);
#endif
#include "pedido-articulo.hpp"

LineaPedido::LineaPedido(double pv, unsigned cant): p_venta(pv), cantidad_(cant){}

const double LineaPedido::precio_venta()const{
	return p_venta;
}

const unsigned LineaPedido::cantidad()const{
	return cantidad_;
}

ostream& operator<<(ostream& os, const LineaPedido& l){
	os<<fixed<<setprecision(2)<<l.precio_venta()<<' '<<"€\t"<<l.cantidad();
	return os;
}

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double precio, unsigned cant){
	as_pedido_artic[&ped].insert(make_pair(&art, LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double precio, unsigned cant){
	as_articulo_ped[&art].insert(make_pair(&ped, LineaPedido(precio, cant)));
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped)const{
	return as_pedido_artic.at(&ped);
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art){
	return as_articulo_ped[&art];
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os){
	double tot=0;
	for(const auto& it:as_pedido_artic){
		os<<"Pedido num. "<<it.first->numero()<<endl<<"Cliente: "<<it.first->tarjeta()->titular()->nombre()<< "\t"<<endl<<"Fecha: "<<it.first->fecha()<<endl<<it.second;
		tot+=it.first->total();
	}
	os<<"TOTAL VENTAS: "<<fixed<<setprecision(2)<<tot<<" €"<<endl;
	return os;
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os){
	for(const auto& it: as_articulo_ped){
		os<<it.second<<endl;
	}
	return os;
}

ostream& operator<<(ostream& os, const Pedido_Articulo::ItemsPedido& ped){
	double importe=0;
	for(const auto& par: ped){
		const Articulo& art = *par.first;
		const LineaPedido& l = par.second;
		os << art <<' '<< l.precio_venta() << ' '<< l.cantidad() << endl;
		importe+=l.precio_venta()*l.cantidad();
	}
	os<<endl<<"Importe total: "<<fixed<<setprecision(2)<< importe<< endl<<"Número de ejemplares: " << ped.size() << endl;
	return os;
}

ostream& operator<<(ostream& os, const Pedido_Articulo::Pedidos& ped){
	double importe=0;
	for (auto const& par: ped){
		const Pedido& p=*par.first;
		const LineaPedido& l= par.second;
		os<<p.total()<<" € "<<l.cantidad()<<' '<<p.fecha()<<endl;
		importe+=l.precio_venta()*l.cantidad();
	}
	os<<endl<<"Importe total: "<<fixed<< setprecision(2) <<importe<<" €"<<endl;
	return os;
}
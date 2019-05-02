#include "pedido.hpp"

#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

int Pedido::N_pedidos=0;

Pedido::Pedido(Usuario_Pedido& us_ped, Pedido_Articulo& ped_art, Usuario& us, const Tarjeta& tar, const Fecha& f):num_(N_pedidos+1), tarjeta_(&tar), fecha_(f), total_(0){
	if(us.n_articulos()==0){
		throw Vacio(us);
	}
	if(&us!=tar.titular()){
		throw Impostor(us);
	}
	if(f>tar.caducidad()){
		throw Tarjeta::Caducada(tar.caducidad());
	}
	set<LibroDigital*> exp;
	for(auto c: us.compra()){
		if(ArticuloAlmacenable* aa=dynamic_cast<ArticuloAlmacenable*>(c.first)){
			if(c.second>aa->stock()){
				VaciaCarrito(us);
				throw SinStock(c.first);
			}
		}else if(LibroDigital* lb=dynamic_cast<LibroDigital*>(c.first)){
			if(lb->f_expir()<Fecha()){
				exp.insert(lb);
			}
		}else{
			throw logic_error("Tipo de articulo desconocido");
		}
	}

	for (auto art : exp)
        us.compra(*art, 0);

    if (us.compra().size() == 0)
        throw Vacio(us);

	/*for(const auto it: us.compra()){
		if(it.second>it.first->stock()){
			VaciaCarrito(us);
			throw SinStock(it.first);
		}
	}*/
	for(const auto pf: us.compra()){
		Articulo& art=*pf.first;
		ped_art.pedir(*this, *pf.first, pf.first->precio(), pf.second);
		ped_art.pedir(*pf.first, *this, pf.first->precio(), pf.second);
		total_+=pf.first->precio()*pf.second;
		if(auto* ArtAlm=dynamic_cast<ArticuloAlmacenable*>(&art))
			ArtAlm->stock()-=pf.second;
	}
	VaciaCarrito(us);
	us_ped.asocia(*this, us);
	us_ped.asocia(us, *this);
	++N_pedidos;
}

int Pedido::numero()const{
	return num_;
}

const Tarjeta* Pedido::tarjeta()const{
	return tarjeta_;
}

Fecha Pedido::fecha()const{
	return fecha_;
}

double Pedido::total()const{
	return total_;
}

int Pedido::n_total_pedidos(){
	return N_pedidos;
}

Pedido::Vacio::Vacio(const Usuario& user): us(user){}

Pedido::Impostor::Impostor(const Usuario& user): imp_(user){}

Pedido::SinStock::SinStock(const Articulo* art): art_(art){}

void Pedido::VaciaCarrito(Usuario& user){
	Usuario::Articulos art=user.compra();
	for(const auto it: art){
		user.compra(*it.first, 0);
	}
}

ostream& operator<<(ostream& os, const Pedido& ped){
	os <<"Núm. pedido: "<<ped.numero()<<endl<< "Fecha:       "<< ped.fecha()<<endl<<"Pagado con:  "<<ped.tarjeta()->tipo()<<" nº: "<<ped.tarjeta()->numero()<<endl<< "Importe:     "<<fixed<< setprecision(2) << ped.total()<< " €" << endl;
	return os;
}

#include "articulo.hpp"
//Autor

Autor::Autor(const Cadena& nom, const Cadena& apell, const Cadena& dir):nom_(nom), apell_(apell), dir_(dir){}

const Cadena& Autor::nombre()const noexcept{
	return nom_;
}

const Cadena& Autor::apellidos()const noexcept{
	return apell_;
}

const Cadena& Autor::direccion()const noexcept{
	return dir_;
}

//Articulo

Articulo:: Articulo(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec):aut(au), refer(cod), titul(tit), fech_p(f), valor(prec){
	if(aut.empty()){
		throw Autores_vacios();
	}
}

const Articulo::Autores& Articulo::autores()const{
	return aut;
}

const Cadena& Articulo::referencia()const{
	return refer;
}

const Cadena& Articulo:: titulo()const{
	return titul;
}

const Fecha& Articulo:: f_publi()const{
	return fech_p;
}

double Articulo::precio()const{
	return valor;
}

double& Articulo:: precio(){
	return valor;
}

ostream& operator<<(ostream& os, const Articulo& art){
	os<<"["<<setw(3)<<setfill('0')<<art.referencia()<<"] \""<< art.titulo()<< "\", de ";
    auto autor = art.autores().begin();
    os << (*autor)->apellidos();
    for(++autor; autor != art.autores().end(); ++autor)
        os << ", " << (*autor)->apellidos();
    os<<". ";
    int anio = art.f_publi().anno();
    os <<anio<<". "<<fixed<< setprecision(2)<<art.precio()<<" €\n\t";
	art.impresion_especifica(os);
	return os;
}

//ArticuloAlmacenable

ArticuloAlmacenable::ArticuloAlmacenable(const Autores& au,const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned stock):Articulo(au,cod,tit,f,prec), stock_(stock){}

unsigned ArticuloAlmacenable::stock()const{
	return stock_;
}

unsigned& ArticuloAlmacenable::stock(){
	return stock_;
}

//Libro

Libro::Libro(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned pags, unsigned stock):ArticuloAlmacenable(au,cod,tit,f,prec,stock), n_pag_(pags){}

unsigned Libro::n_pag()const{
	return n_pag_;
}

void Libro::impresion_especifica(ostream& os)const{
	os<<n_pag_<<" págs., "<<stock_<<" unidades.";
}

//Cederron

Cederron::Cederron(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned tama, unsigned stock):ArticuloAlmacenable(au,cod,tit,f,prec,stock), tam_(tama){}

unsigned Cederron::tam()const{
	return tam_;
}

void Cederron::impresion_especifica(ostream& os)const{
	os<<tam_<<" MB, "<<stock_<<" unidades.";
}

//LibroDigital

LibroDigital::LibroDigital(const Autores& au, const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, const Fecha& fExpir):Articulo(au,cod,tit,f,prec), f_expir_(fExpir){}

const Fecha& LibroDigital::f_expir()const{
	return f_expir_;
}

void LibroDigital::impresion_especifica(ostream& os)const{
	os << "A la venta hasta el " << f_expir_ << '.';
}
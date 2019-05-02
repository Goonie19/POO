#include "articulo.hpp"
//constructores
Articulo:: Articulo(const Cadena& cod, const Cadena& tit, const Fecha& f, double prec, unsigned stock):refer(cod), titul(tit), fech_p(f), valor(prec), existencias(stock){}

Cadena Articulo::referencia()const{
	return refer;
}

Cadena Articulo:: titulo()const{
	return titul;
}

Fecha Articulo:: f_publi()const{
	return fech_p;
}

double Articulo::precio()const{
	return valor;
}

double& Articulo:: precio(){
	return valor;
}

unsigned Articulo::stock()const{
	return existencias;
}

unsigned& Articulo::stock(){
	return existencias;
}

ostream& operator<<(ostream& os, const Articulo& art){
	os<<"["<<art.referencia()<<"] "<< art.titulo()<<", "<<art.f_publi().anno()<<". "<< setprecision(2)<< art.precio()<< "€."<<endl;
	return os;
}
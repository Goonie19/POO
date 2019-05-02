#include "tarjeta.hpp"

bool luhn(const Cadena& numero);

Numero::Numero(const Cadena& num){
	if(num.length()==0){
		throw Incorrecto(Razon::LONGITUD);
	}
	Cadena::iterator it=remove_if(num.begin(), num.end(), [](char c){return isspace(c);});
	num_=num.substr(0, it-num.begin());
	Cadena::iterator it2=find_if(num_.begin(), num_.end(), not1(EsDigito()));
	if(it2!=num_.end()){
		throw Incorrecto(Razon::DIGITOS);
	}
	if(num_.length()<13 || num.length()>19){
		throw Incorrecto(Razon::LONGITUD);
	}
	if(!luhn(num_)){
		throw Incorrecto(Razon::NO_VALIDO);
	}
}

Numero::operator const char*()const{
	return num_.c_str();
}

bool operator<(const Numero& num, const Numero& num2){
	return (num.num_<num2.num_);
}

bool operator<(const Tarjeta& t, const Tarjeta& t2){
	return (t.numero()<t2.numero());
}

Tarjeta:: Tarjeta(Tipo tip, const Numero& num, Usuario& us, const Fecha& caducidad):tarjet(tip), num_(num), user(&us), caduci(caducidad),tit_fac((us.nombre()+" ")+us.apellidos()){
	if (caduci<Fecha()){
		throw Caducada(caduci);
	}else{
		us.es_titular_de(*this);
	}
}

void Tarjeta::anula_titular(){
	user=nullptr;
}

Tarjeta::~Tarjeta(){
	if(user){
		user->no_es_titular_de(*this);
	}
}

ostream& operator<<(ostream& os, const Tarjeta::Tipo& tipo){
	int tip=tipo;
	switch(tip){
		case 0: os<<"VISA ";break;
		case 1: os<< "Mastercard ";break;
		case 2: os<<"Maestro ";break;
		case 3: os<<"JCB ";break;
		case 4: os<<"AmericanExpress ";break;
	}
	return os;
}

ostream& operator<<(ostream& os, const Tarjeta& t){
	os<<t.tipo()<<endl<<t.numero()<<endl<<t.titular_facial()<<endl<<"Caduca: "<< setfill('0')<< setw(2)<< t.caducidad().mes()<<"/"<<t.caducidad().anno()%100<<endl;
	return os;
}

//Implementacion clases de excepcion

Numero::Incorrecto::Incorrecto(Razon t): raz(t){}

Numero::Razon Numero::Incorrecto::razon()const{
	return raz;
}

Tarjeta::Caducada::Caducada(const Fecha& f): fech_cad(f){}

const Fecha& Tarjeta::Caducada::cuando()const{
	return fech_cad;
}


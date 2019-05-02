#include "tarjeta.hpp"

bool luhn(const Cadena& numero);

Numero::Numero(const Cadena& num){
	if(num.length()==0){
		throw Incorrecto(Razon::LONGITUD);
	}
	char* aux=new char[num.length()+1];
	int j=0;
	bool dig=false;
	for(size_t i=0; i<num.length();++i){
		if(!isspace(num[i])){
			aux[j]=num[i];
			++j;
		}
	}
	aux[j]='\0';
	Cadena aux2(aux);
	delete[] aux;
	size_t r=0;
	while(!dig && r<aux2.length()){
		if(aux2[r]<'0' || aux2[r]>'9'){
			dig=true;
		}else{
			++r;
		}
	}
	if(r!=aux2.length()){
		throw Incorrecto(Razon::DIGITOS);
	}
	if(aux2.length()<13 || aux2.length()>19){
		throw Incorrecto(Razon::LONGITUD);
	}
	if(luhn(aux2)==false){
		throw Incorrecto(Razon::NO_VALIDO);
	}
	num_=aux2;
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
	if (caduci<Fecha()){//por alguna razon, no le resta el dia a la fecha en el check, revisa fecha 
		throw Caducada(caduci);
	}else{
		us.es_titular_de(*this);
	}
}

Tarjeta::Tipo Tarjeta::tipo()const{
	return tarjet;
}

Numero Tarjeta::numero()const{
	return num_;
}

const Usuario* Tarjeta::titular()const{
	return user;
}

Fecha Tarjeta::caducidad()const{
	return caduci;
}

Cadena Tarjeta::titular_facial()const{
	return tit_fac;
}

void Tarjeta::anula_titular(){
	user=nullptr;
}

Tarjeta::~Tarjeta(){
	if(user){
		user->no_es_titular_de(*this);
	}
}

ostream& operator<<(ostream& os, Tarjeta::Tipo const& tipo){
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


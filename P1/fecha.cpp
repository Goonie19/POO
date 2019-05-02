#include "fecha.hpp"

using namespace std;

Fecha& Fecha::operator+=(const int n){
    time_t secs = n * 24 * 3600;
    tm temp{};
    time_t fech{};
    tm * time;
    temp.tm_mday = this->d;
    temp.tm_mon = this->m - 1;
    temp.tm_year = this->a - 1900;
    fech = mktime(&temp);
    fech = fech + secs;
	time = localtime(&fech);
    this->d=time->tm_mday;
    this->m=time->tm_mon + 1;
    this->a=time->tm_year + 1900;
    validaFecha(this->d,this->m, this->a);
    return *this;
}
Fecha& Fecha::operator-=(const int n){
	return *this+=(-n);
}

Fecha& Fecha::operator++(){
	return *this+=1;
}

Fecha& Fecha::operator--(){
	return *this+=(-1);
}

Fecha Fecha::operator++(int){
	Fecha f(*this);
	*this+=1;
	return f;
}

Fecha Fecha::operator--(int){
	Fecha f(*this);
	*this+=(-1);
	return f;
}

Fecha Fecha::operator+(int n)const{
	Fecha f(*this);
	return f+=n;
}

Fecha Fecha::operator-(int n)const{
	Fecha f(*this);
	return f+=(-n);
}

bool operator<(const Fecha& t,const Fecha& f){
	bool comp=false;
	if(t.anno()<f.anno()){
		comp=true;
	}else{
		if(t.anno()==f.anno()){
			if(t.mes()<f.mes()){
				comp=true;
			}else{
				if(t.mes()==f.mes()){
					if(t.dia()<f.dia()){
						comp=true;
					}
				}
			}
		}
	}
	return comp;
}

bool operator>(const Fecha& t,const Fecha& f){
	return (f<t);
}

bool operator==(const Fecha& t,const Fecha& f){
	bool comp=true;
	if(t.anno()!=f.anno()){
		comp=false;
	}
	if(t.mes()!=f.mes()){
		comp=false;
	}
	if(t.dia()!=f.dia()){
		comp=false;
	}
	return comp;
}

bool operator!=(const Fecha& t, const Fecha& f){
	return !(t==f);
}

bool operator<=(const Fecha& t,const Fecha& f){
	return !(f<t);
}

bool operator>=(const Fecha& t,const Fecha& f){
	return !(t<f);
}

ostream& operator<<(ostream& os, const Fecha& f){
	os<<f.cadena();
	return os;
}

istream& operator>>(istream& is, Fecha& f){
	char cad[11];
	is.getline(cad, 11);
	try{
		f=Fecha(cad);
	}catch(Fecha::Invalida& e){
		is.setstate(std::ios_base::failbit);
		throw;
	}
	return is;
}

const char * Fecha:: cadena()const{
	int result1, result2, result3, result4, result5, mes, anno;
	anno=this->a;
	int regular[]={0,3,3,6,1,4,6,2,5,0,3,5};
	int bisiesto[]={0,3,4,0,2,5,0,3,6,1,4,6};
	if(anno%4==0 && (anno%100!=0 || anno%400==0)){
		mes=bisiesto[this->m-1];
	}else{
		mes=regular[this->m-1];
	}
	result1=(anno-1)%7;
	result2=(anno-1)/4;
	result3=(3*(((anno-1)/100)+1))/4;
	result4=(result2-result3)%7;
	result5=d%7;
	char const* dias[]={"domingo","lunes", "martes", "miércoles", "jueves","viernes", "sabado"};//ARREGLA EL MES
	char const* mesN[]={"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre","octubre", "noviembre", "diciembre"};
	static char fecha[40];
	sprintf(fecha,"%s %i de %s de %i", dias[(result1+result4+mes+result5)%7], this->d, mesN[this->m-1], this->a);
	return (const char*)fecha;
}

Fecha::Fecha(int dia, int mes, int anno):d(dia), m(mes), a(anno){
	time_t tiempo=time(nullptr);;
	struct tm actual=*localtime(&tiempo);
	if(dia==0){
		this->d=actual.tm_mday;
	}
	if(mes==0){
		this->m=actual.tm_mon+1;
	}
	if(anno==0){
		this->a=actual.tm_year+1900;
	}
	validaFecha(this->d, this->m, this->a);
}

Fecha:: Fecha(const char * cadena){
	time_t tiempo=time(nullptr);
	struct tm actual=*localtime(&tiempo);
	if(sscanf(cadena, "%d/%d/%d", &this->d, &this->m, &this->a)==3){
		if(this->a==0){
			this->a=actual.tm_year+1900;
		}
		if(this->m==0){
			this->m=actual.tm_mon+1;
		}
		if(this->d==0){
			this->d=actual.tm_mday;
		}
		validaFecha(this->d, this->m, this->a);
	}else
		throw Invalida("El formato de la cadena no es el correcto");
}

void Fecha:: validaFecha(int dia, int mes, int anno){
	switch(mes){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:{
			if(dia<0 || dia>31){
				throw Invalida("Este mes tiene 31 dias");
			}
		};break;
		case 4:
		case 6:
		case 9:
		case 11:{
			if(dia<0 || dia>30){
				throw Invalida("Este mes tiene 30 dias");
			}
		};break;
		case 2:{
			if(a % 4 == 0 && (a % 400 == 0 || a % 100 != 0)){
				if(dia<0 || dia>29){
					throw Invalida("Este mes solo tiene 29 dias");
				}
			}else{
				if(dia<0 || dia>28){
					throw Invalida("Este mes solo tiene 28 dias");
				}
			}
		};break;
		default: throw Invalida("El mes introducido no esta entre 1 y 12 o no ha sido introducido si se uso cadena. Compruebe de nuevo la fecha");break;
	}
	if(anno>AnnoMaximo || anno<AnnoMinimo){
		throw Invalida("El año introducido no esta entre 1902 y 2037 o no ha sido introducido si se uso cadena, compruebe de nuevo la fecha.");
	}
}

Fecha:: Invalida::Invalida(const char* razon): razon(razon){}

const char * Fecha:: Invalida:: por_que()const{
	return razon;
}

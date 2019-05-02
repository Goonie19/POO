
#include "fecha.hpp"
#include <iostream>
#include <cstdio>
#include <chrono>
//termnia el constructor de fecha con cadenas y sobrecarga los operadores para terminar 
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

Fecha& Fecha::operator++(const int){
	return *this+=1;
}

Fecha& Fecha::operator--(const int){
	return *this+=(-1);
}

Fecha& Fecha::operator+(const int n){
	return *this+=n;
}

Fecha& Fecha::operator-(const int n){
	return *this+=(-n);
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
	bool comp=false;
	if(t.anno()>f.anno()){
		comp=true;
	}else{
		if(t.anno()==f.anno()){
			if(t.mes()>f.mes()){
				comp=true;
			}else{
				if(t.mes()==f.mes()){
					if(t.dia()>f.dia()){
						comp=true;
					}
				}
			}
		}
	}
	return comp;
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

bool operator<=(const Fecha& t,const Fecha& f){
	bool comp=true;
	if(t.anno()>f.anno()){
		comp=false;
	}else{
		if(t.anno()==f.anno()){
			if(t.mes()>f.mes()){
				comp=false;
			}else{
				if(t.mes()==f.mes()){
					if(t.dia()>f.dia()){
						comp=false;
					}
				}
			}
		}
	}
	return comp;
}

bool operator>=(const Fecha& t,const Fecha& f){
	bool comp=true;
	if(t.anno()<f.anno()){
		comp=false;
	}else{
		if(t.anno()==f.anno()){
			if(t.mes()<f.mes()){
				comp=false;
			}else{
				if(t.mes()==f.mes()){
					if(t.dia()<f.dia()){
						comp=false;
					}
				}
			}
		}
	}
	return comp;
}

Fecha:: operator const char* (){
	return this->cadena();
}
//termina mañana 
const char * Fecha:: cadena(){
	int result1, result2, result3, result4, result5, dia, mes, anno;
	dia=this->d;
	anno=this->a;
	int regular[]={0,3,3,6,1,4,6,2,5,0,3,5};
	int bisiesto[]={0,3,4,0,2,5,0,3,6,1,4,6};
	if(anno%4==0 && anno%100!=0 && anno%400==0){
		mes=bisiesto[this->m-1];
	}else{
		mes=regular[this->m-1];
	}
	result1=(anno-1)%7;
	result2=(anno-1)/4;
	result3=(3*(((anno-1)/100)+1))/4;
	result4=(result2-result3)%7;
	result5=d%7;
	char const* dias[]={"Domingo","Lunes", "Martes", "Miercoles", "Jueves","Viernes", "Sabado"};//ARREGLA EL MES
	char const* mesN[]={"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre","octubre", "noviembre", "diciembre"};
	char* fecha=new char[40];
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

Fecha::Fecha(const Fecha& F){
	time_t tiempo=time(nullptr);
	struct tm actual=*localtime(&tiempo);
	if(F.d==0){
		this->d=actual.tm_mday;
	}else{
		this->d=F.d;
	}
	if(F.m==0){
		this->m=actual.tm_mon;
	}else{
		this->m=F.m;
	}
	if(F.a==0){
		this->a=actual.tm_year+1900;
	}else{
		this->a=F.a;
	}
	validaFecha(this->d, this->m, this->a);
}

Fecha:: Fecha(const char * cadena){
	time_t tiempo=time(nullptr);
	struct tm actual=*localtime(&tiempo);
	sscanf(cadena, "%d/%d/%d", &this->d, &this->m, &this->a);
	if(this->a==0){
		this->a=actual.tm_year+1900;
	}
	if(this->m==0){
		this->m=actual.tm_mon;
	}
	if(this->d==0){
		this->d=actual.tm_mday;
	}
	validaFecha(this->d, this->m, this->a);
}

int Fecha:: anno()const{
	return this->a;
}

int Fecha:: mes()const{
	return this->m;
}

int Fecha:: dia()const{
	return this->d;
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
			if(anno%4==0 && anno%100!=0 && anno%400==0){
				if(dia<0 || dia>29){
					throw Invalida("Este mes solo tiene 29 dias");
				}
			}else{
				if(dia<0 && dia>28){
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

#include <iostream>
#include "cadena.hpp"
#include <string.h>
using namespace std;

Cadena& Cadena::operator=(Cadena& cad2){
	if(&cad2!=this){
		delete [] s_;
		s_=new char[cad2.tam_+1];
		strcpy(s_, cad2.s_);
		tam_=cad2.tam_;
	}
	return *this;
}

Cadena& Cadena::operator=(const char* cad2){
	delete[] s_;
	tam_=strlen(cad2);
	s_=new char[tam_+1];
	strcpy(s_, cad2);
	return *this;
}

Cadena& Cadena::operator+=(const Cadena& cad2){
	Cadena aux(*this);
	delete [] s_;
	tam_+=cad2.tam_;
	s_=new char[tam_+1];
	strcpy(s_, aux.s_);
	strcat(s_, cad2.s_);
	return *this;
}

Cadena& Cadena::operator+=(const char* cad1){
	Cadena aux(*this);
	tam_+=strlen(cad1);
	delete[] s_;
	s_=new char[tam_+1];
	strcpy(s_, aux.s_);
	strcat(s_,cad1);
	return *this;
}

Cadena operator+(Cadena& cad1, Cadena& cad2){
	Cadena cad3(cad1);
	cad3+=cad2;
	return cad3;
}

Cadena operator+(Cadena& cad1, const char* cad2){
	Cadena cad3(cad1);
	cad3+=cad2;
	return cad3;
}

char Cadena::operator[](size_t i)const noexcept{
	return s_[i];
}

char& Cadena::operator[](size_t i)noexcept{
	return s_[i];
}

bool operator<(Cadena& cad1, Cadena& cad2){
	bool compmenor=false, compmayor=false;
	size_t i=0;
	while(i<cad1.length() && i<cad2.length() && !compmenor && !compmayor){
		if((cad1[i])<(cad2[i])){
			compmenor=true;
		}else{
			if((cad1[i])>(cad2[i])){
				compmayor=true;
			}else{
				++i;
			}
		}
	}
	return compmenor;
}

bool operator>(Cadena& cad1, Cadena& cad2){
	bool compmayor=false, compmenor=false;
	size_t i=0;
	while(i<cad1.length() && i<cad2.length() && !compmayor && !compmenor){
		if(cad1[i]>cad2[i]){
			compmayor=true;
		}else{
			if(cad1[i]<cad2[i]){
				compmenor=true;
			}else{
				++i;
			}
		}
	}
	return compmayor;
}

bool operator==(Cadena& cad1,Cadena& cad2){
	bool comp=true;
	size_t i=0;
	if(cad1.length()!=cad2.length()){
		comp=false;
	}else{
		while(i<cad1.length() && comp){
			if(cad2[i]==cad1[i]){
				++i;
			}else{
				comp=false;
			}
		}
	}
	return comp;
}

bool operator!=(Cadena& cad1, Cadena& cad2){
	bool comp;
	if(cad1==cad2){
		comp=false;
	}else{
		comp=true;
	}
	return comp;
}

bool operator<=(Cadena& cad1, Cadena& cad2){
	bool comp;
	if(cad1<cad2 || cad1==cad2){
		comp=true;
	}else{
		comp=false;
	}
	return comp;
}

bool operator>=(Cadena& cad1, Cadena& cad2){
	bool comp;
	if(cad1>cad2 || cad1==cad2){
		comp=true;
	}else{
		comp=false;
	}
	return comp;
}

Cadena::operator const char*(){
	return (const char*) s_;
}

char Cadena:: at(size_t i)const{
	if(i>tam_){
		throw std::out_of_range("Error, indice fuera de rango");
	}else{
		return (*this)[i];
	}
}

char Cadena:: at(size_t i){
	if(i>tam_){
		throw std::out_of_range("Error, indice fuera de rango");
	}else{
		return (*this)[i];
	}
}

//Constructores

Cadena::Cadena(size_t tam, char cad){
	tam_=tam;
	s_=new char[tam_+1];
	for(size_t i=0;i<tam;++i){
		s_[i]=cad;
	}
	s_[tam]='\0';
}

Cadena::Cadena(Cadena& cad){
	tam_=cad.tam_;
	s_=new char[cad.tam_+1];
	strcpy(s_, cad.s_);
}

Cadena::Cadena(const char* cad){
	tam_=strlen(cad);
	s_=new char[tam_+1];
	strcpy(s_,cad);
}

size_t Cadena:: length()const{
	return tam_;
}

Cadena Cadena:: substr(size_t i, size_t iteraciones){
	Cadena cadaux(iteraciones);
	if(i+iteraciones>=this->tam_){
		throw std::out_of_range("El numero de caracteres o el indice esta fuera de rango");
	}else{
		for(size_t j=0;j<iteraciones;++j){
			cadaux[j]=s_[i];
			++i;
		}
	}
	return cadaux;
}

Cadena::~Cadena(){
	delete[] s_;
}

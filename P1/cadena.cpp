#include "cadena.hpp"

Cadena& Cadena::operator=(const Cadena& cad2){
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

Cadena& Cadena::operator=(Cadena&& cad2){
	delete[] s_;
	s_=new char[cad2.tam_+1];
	tam_=0;
	strcpy(s_,cad2.s_);
	tam_=cad2.tam_;
	cad2.s_=nullptr;
	cad2.tam_=0;
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

Cadena operator+(const Cadena& cad1, const Cadena& cad2){
	Cadena cad3(cad1);
	cad3+=cad2;
	return cad3;
}

Cadena Cadena::operator+(const char* cad2){
	Cadena cad3(*this);
	cad3+=cad2;
	return cad3;
}

char Cadena::operator[](size_t i)const noexcept{
	return s_[i];
}

char& Cadena::operator[](size_t i)noexcept{
	return s_[i];
}

bool operator<(const Cadena& cad1, const Cadena& cad2){
	return !(cad1>cad2 || cad1==cad2);
}

bool operator>(const Cadena& cad1,const Cadena& cad2){
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

bool operator==(const Cadena& cad1,const Cadena& cad2){
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

bool operator!=(const Cadena& cad1, const Cadena& cad2){
	bool comp;
	if(cad1==cad2){
		comp=false;
	}else{
		comp=true;
	}
	return comp;
}

bool operator<=(const Cadena& cad1,const Cadena& cad2){
	bool comp;
	if(cad1<cad2 || cad1==cad2){
		comp=true;
	}else{
		comp=false;
	}
	return comp;
}

bool operator>=(const Cadena& cad1,const Cadena& cad2){
	bool comp;
	if(cad1>cad2 || cad1==cad2){
		comp=true;
	}else{
		comp=false;
	}
	return comp;
}

ostream& operator<<(ostream& os, const Cadena& cad){
	os<<cad.c_str();
	return os;
}

istream& operator>>(istream& is, Cadena& cad){
	char cadena[33];
	int i=0;
	char aux;
	while(isspace(is.get()) && is.good()){}
	is.unget();
	while(i<32 && !isspace(is.peek()) && is.good() && is.peek()!= '\n' && is.peek()!='\0'){
		aux=is.get();
		if(is.good()){
			cadena[i]=aux;
			++i;
		}
	}
	cadena[i]='\0';
	if(i!=0){
		cad=Cadena(cadena);
	}else{
		Cadena cade;
		cad=cade;
	}
	return is;
}

const char* Cadena:: c_str()const{
	return (const char*) s_;
}

char Cadena:: at(size_t i)const{
	if(i>=tam_){
		throw std::out_of_range("Error, indice fuera de rango");
	}else{
		return (*this)[i];
	}
}

char& Cadena:: at(size_t i){
	if(i>=tam_){
		throw std::out_of_range("Error, indice fuera de rango");
	}else{
		return (*this)[i];
	}
}

//Constructores

Cadena::Cadena(unsigned tam, char cad):tam_(tam){
	s_=new char[tam_+1];
	for(size_t i=0;i<tam;++i){
		s_[i]=cad;
	}
	s_[tam_]='\0';
}

Cadena::Cadena(const Cadena& cad){
	tam_=cad.tam_;
	s_=new char[cad.tam_+1];
	strcpy(s_, cad.s_);
}

Cadena::Cadena(Cadena&& str):s_(str.s_), tam_(str.tam_){
	str.tam_=0;
	str.s_=nullptr;
}

Cadena::Cadena(const char* cad):tam_(strlen(cad)){
	s_=new char[tam_+1];
	strcpy(s_,cad);
}

Cadena Cadena:: substr(int i, int iteraciones)const{
	if(i<0|| iteraciones<0|| i+iteraciones>tam_ || i>iteraciones){
		throw std::out_of_range("El indice es negativo.");
	}
	char* cadaux=new char[iteraciones+1];
	strncpy(cadaux,s_+i, iteraciones);
	cadaux[iteraciones]='\0';
	Cadena c_aux(cadaux);
	delete[] cadaux;
	return c_aux;
}

Cadena::~Cadena(){
	delete[] s_;
}

#ifndef CADENA_HPP
#define CADENA_HPP
#include <iostream>
#include <iterator>
#include <cstring>
#include <stdexcept>
using namespace std;

class Cadena{
	public:
		//operadores
		Cadena& operator=(const Cadena& cad2);
		Cadena& operator=(Cadena&& cad2);
		Cadena& operator+=(const Cadena& cad2);
		Cadena& operator+=(const char * cadena);
		Cadena operator+(const char * cad2);
		Cadena& operator=(const char* cad2);
		char operator[](size_t i)const noexcept;
		char& operator[](size_t i)noexcept;
		const char* c_str()const;
		//Constructores
		explicit Cadena(unsigned tam=0, char cad=' ');
		Cadena(const Cadena& str);
		Cadena(Cadena&& str);
		Cadena(const char* str);
		//metodo observador
		size_t length()const noexcept{return tam_;}
		char at(size_t i)const;
		Cadena substr(int i, int iteraciones)const;
		//metodos
		char& at(size_t i);
		//typedefs
		typedef char * iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		//iteradores begin
		inline iterator begin()const{return s_;}
		inline const_iterator cbegin()const{return s_;}
		//iteradores end
		inline iterator end()const{return s_+tam_;}
		inline const_iterator cend()const{return s_+tam_;}
		//reverse begin
		inline reverse_iterator rbegin()const{return (reverse_iterator) end();}
		inline const_reverse_iterator crbegin()const{return (const_reverse_iterator) end();}
		//reverse end
		inline reverse_iterator rend()const{return (reverse_iterator) begin();}
		inline const_reverse_iterator crend()const{return (const_reverse_iterator) begin();}
		//destructor
		~Cadena();

	private:
		char* s_;
		size_t tam_;
};
Cadena operator+(const Cadena& cad1,const Cadena& cad2);
bool operator<(const Cadena& cad1,const Cadena& cad2);
bool operator>(const Cadena& cad1, const Cadena& cad2);
bool operator==(const Cadena& cad1, const Cadena& cad2);
bool operator!=(const Cadena& cad1,const Cadena& cad2);
bool operator<=(const Cadena& cad1, const Cadena& cad2);
bool operator>=(const Cadena& cad1, const Cadena& cad2);
ostream& operator<<(ostream& os, const Cadena& cad);
istream& operator>>(istream& is, Cadena& cad);

namespace std {
template <> struct hash<Cadena> {
size_t operator()(const Cadena& cad) const
{ // conversión const char* ->string
return hash<string>{}(cad.c_str());
}
};
}

#endif

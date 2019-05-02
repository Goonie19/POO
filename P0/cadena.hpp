#include <iostream>

class Cadena{
	public:
		//operadores
		Cadena& operator=(Cadena& cad2);
		Cadena& operator+=(const Cadena& cad2);
		Cadena& operator+=(const char * cadena);
		Cadena& operator=(const char* cad2);
		char operator[](size_t i)const noexcept;
		char& operator[](size_t i)noexcept;
		operator const char*();
		//Constructores
		Cadena(size_t tam=0, char cad=' ');
		Cadena(Cadena& str);
		Cadena(const char* str);
		//metodo observador
		size_t length()const;
		char at(size_t i)const;
		Cadena substr(size_t i, size_t iteraciones);
		//metodos
		char at(size_t i);
		//destructor
		~Cadena();

	private:
		char* s_;
		size_t tam_;
};
Cadena operator+(Cadena& cad1, Cadena& cad2);
Cadena operator+(Cadena& cad1, const char * cad2);
bool operator<(Cadena& cad1, Cadena& cad2);
bool operator>(Cadena& cad1, Cadena& cad2);
bool operator==(Cadena& cad1, Cadena& cad2);
bool operator!=(Cadena& cad1,Cadena& cad2);
bool operator<=(Cadena& cad1, Cadena& cad2);
bool operator>=(Cadena& cad1, Cadena& cad2);
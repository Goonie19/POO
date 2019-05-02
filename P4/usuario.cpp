#include "usuario.hpp"

Usuario::Usuarios Usuario::list_user;

//Constructor de clase clave
Clave:: Clave(const char * clave){
	if(strlen(clave)<5){
		throw Incorrecta(Clave::CORTA);
	}else{
		const char auxsalt[65]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
		char* cla;
		random_device ran;
		uniform_int_distribution<int> r(0,63);
		//srand(time(nullptr));
		char salt[2];
		salt[0]=auxsalt[r(ran)];
		salt[1]=auxsalt[r(ran)];
		//salt[0]=auxsalt[rand()%65];
		//salt[1]=auxsalt[rand()%65];
		cla=crypt(clave, salt);
		if(cla==nullptr){
			throw Incorrecta(Clave::Razon::ERROR_CRYPT);
		}
		pass=cla;
	}
}

const Cadena& Clave::clave()const{
	return pass;
}

//Constructor de clase Incorrecta dentro de clase Clave
Clave::Incorrecta:: Incorrecta(Razon raz):raz(raz){}


//Metodo observador que devuelve la razon por la que la excepcion fue lanzada
Clave::Razon Clave::Incorrecta::razon()const{return raz;}


//Metodo que verifica la clave
bool Clave::verifica(const char* cla)const{
	bool comp=false;
	char cad[2];
	cad[0]=pass[0];
	cad[1]=pass[1];
	if(strcmp(pass.c_str(), crypt(cla, cad))==0){
		comp=true;
	}
	return comp;
}
//Clase Usuario
Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellido, const Cadena& direccion, const Clave& clav):name(nombre), apell(apellido), user_dir(direccion), pass_(clav){
	if(list_user.insert(id).second==false){
		throw Id_duplicado(id);
	}else{
		id_user=id;
	}
}

void Usuario::es_titular_de(const Tarjeta& tar){
	if(tar.titular()==this){
		list_tarj[tar.numero()]=const_cast<Tarjeta*>(&tar);
	}
}

void Usuario::no_es_titular_de(Tarjeta& tar){
	list_tarj.erase(tar.numero());
}

void Usuario::compra(const Articulo& art, unsigned pedido){
	if(pedido==0){
		list_art.erase(const_cast<Articulo*>(&art));
	}else{
		list_art[const_cast<Articulo*>(&art)]=pedido;
	}
}

//destructor de ususario
Usuario::~Usuario(){
	for(Tarjetas::iterator i=list_tarj.begin(); i!=list_tarj.end();++i){
		i->second->anula_titular();
	}
	list_user.erase(id_user);
}

//Excepcion usuario repetido 

Usuario::Id_duplicado::Id_duplicado(const Cadena& id_repe): id_rep(id_repe){}

const Cadena& Usuario::Id_duplicado::idd()const{
	return id_rep;
}

//funciones externas y operadores

ostream& operator<<(ostream& os, const Usuario& user){
	os<<user.id_user<<" ["<<user.pass_.clave()<<"] "<<user.name<<" "<< user.apell<<endl<<user.user_dir<<endl<<"Tarjetas:"<<endl;
	for(auto t : user.tarjetas()){
		os<<*t.second<<endl;
	}
	return os;
}

void mostrar_carro(ostream& os, const Usuario& user){
	os<<"Carrito de compra de "<<user.id()<<" [Artículos: "<<user.n_articulos()<<"]\n Cant Articulo."<<endl;
	if(user.n_articulos()!=0){
		os << " Cant. Artículo" << endl<< setw(65) << setfill('=') << '\n'  << setfill(' ');
		for (auto const& i : user.compra()){
    	    const Articulo& a = *i.first;
        	os << setw(4) << i.second << "   "<< "[" << a.referencia() << "] \""<< a.titulo() << "\", " << a.f_publi().anno()<< ". " << fixed << setprecision(2) << a.precio()<< " €" << endl;
    	}
    os << endl;
	}
}
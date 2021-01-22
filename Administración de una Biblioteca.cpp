/*
	Nombre: Administración de una Biblioteca
	Autor: Esleiter Jose Fajardo Laya
	Fecha: 10/01/21
	Lugar: Venezuela
*/


#include <iostream>
#include <windows.h>
#include <fstream>
#include <dirent.h>
#include <ctime>

using namespace std;

void clienteEntregaW();

class Fecha {
    private:
    int dia, mes, anio;
    //Comprobar numero de dias para cada meses
    bool fechavalida(int ndia, int nmes, int nanio){
        if(ndia<1 || ndia>31) return false;
        else if (nmes<1 || nmes>12) return false;
        else switch(nmes)
        {
            case 4: case 6: case 9: case 11:
                if(ndia>30) return false;
                break;
            case 2:
                if (ndia>28)return false;
                break;
        }
        return true;
    }
    public:
    Fecha (int d=0, int m=0, int a=0) {
        // Constructor
        if(fechavalida(d,m,a)){
            dia=d; mes=m; anio=a;
        } else {
            cout<<"ERROR: Se trato de introducir fecha incorrecta"<<endl;
            clienteEntregaW();
        }
    }
    int damedia(void){
        return dia;
    }
 
    int damemes(void){
        return mes;
    }
 
    int dameanio(void){
        return anio;
    }
 
    void imprimefecha(void){
        cout<<damedia()<< "-" << damemes()<<"-" << dameanio()<< endl;
    }
 
    void guardarfecha(int d=0, int m=0, int a=0){
        if(fechavalida(d,m,a)) {
            dia=d; mes=m; anio=a;
        } else {
            cout<<"ERROR: Introducir fecha incorrecta"<<endl;
            clienteEntregaW();
        }
    }
 
    void scanfecha(){
        int d, m, a;
        if (scanf("%d-%d-%d",&d,&m,&a)!=3)
        {
            cout << "Error en lectura de fecha.";
            clienteEntregaW();
        }
        else if(fechavalida(d,m,a)) {
            dia=d; mes=m; anio=a;
        }
    }
 
         // declaración de funcioón externa amiga:
    friend int dif_dias (Fecha A, Fecha B);
};
 
//Definición de la función amiga (diferencia en dias):
int dif_dias (Fecha A, Fecha B){
    int d,m,a, dif=0;
 
    // Si estan al reves suspendemos el cálculo:
    if(A.anio > B.anio) return -1;
    else if(A.anio == B.anio && A.mes > B.mes) return -1;
    else if(A.anio == B.anio && A.mes == B.mes && A.dia > B.dia) return -1;
 
    // Si son fechas del mismo año:
    if(A.anio == B.anio) {
        if(A.mes == B.mes) return B.dia-A.dia;
        // Dias por meses completos:   
        for(a=A.mes+1; a<B.mes  ; a++)
        {
            switch(a) {
                case 4: case 6: case 9: case 11:
                     dif+=30;
                     break;
                case 2:
                     dif+=28;
                     break;
                default:
                     dif+= 31;
            }
        }
 
         // Dias que faltan para terminar el mes de A:
        switch(A.mes) {
           case 4: case 6: case 9: case 11:
                dif+=30-A.dia;
                break;
           case 2:
                dif+=28-A.dia;
                break;
           default:
                dif+= 31-A.dia;
        }
        // Dias del mes de B:
        dif+=B.dia;
 
        return dif;
    }
    // Si son dias de años distintos:
    // Años completos de diferencia:
    else dif = (B.anio - (A.anio+1)) * 365;
    // Ahora los meses hasta fin del año de A:   
    for(a=A.mes+1; a<=12  ; a++)
    {
        switch(a) {
            case 4: case 6: case 9: case 11:
                 dif+=30;
                 break;
            case 2:
                 dif+=28;
                 break;
            default:
                 dif+= 31;
        }
    }
 
    // Y los meses desde ppio del año de B:   
    for(a=1; a<B.mes  ; a++)
    {
        switch(a) {
            case 4: case 6: case 9: case 11:
                 dif+=30;
                 break;
            case 2:
                 dif+=28;
                 break;
            default:
                 dif+= 31;
        }
    }
    // Dias que faltan para terminar el mes de A:
    switch(a) {
        case 4: case 6: case 9: case 11:
            dif+=30-A.dia;
            break;
        case 2:
            dif+=28-A.dia;
            break;
        default:
            dif+= 31-A.dia;
    }
    // Dias del mes de B:
    dif+=B.dia;
 
    return dif;
}

bool is_dir(string dir)	{
  DIR * directorio;
  //Comprueba si puede abrir el directorio
	if (directorio = opendir(dir.c_str())) {
		closedir(directorio);
		return true;             
	} else {
		return false;   
	}
}

bool is_file(string file) {
	FILE * archivo;
	//Comprueba si puede abrir el directorio
	if (archivo = fopen(file.c_str(), "r"))
	{
		fclose(archivo);
		return true;           
	} else {
		return false;  
	}
}

//Funcion que registra al cliente
void registrarCliente(){
	ofstream archivo;
	string nombreArchivo,nombreArchivom,info;
	char rpt;
	
	//Solicitamos su cedula
	fflush(stdin);
	cout<<"Digite la cedula del cliente: ";
	getline(cin,nombreArchivo);
	//Establecemos el nombre del archivo personal
	nombreArchivom= ".//clientes//"+nombreArchivo+".txt";
	
	//Comprobamos si existe la carpeta
	if (is_dir(nombreArchivom)){
		cout << "La carpeta existe" << endl;
		system("pause");
		//Comprobamos si existe un archivo para esta persona
	} else if (is_file(nombreArchivom)){
		cout << "El archivo existe" << endl;
		system("pause");
		
	} else {
	//Creamos el archivo
	archivo.open(nombreArchivom.c_str(),ios::out);
	//Si a ocurrido algun error
	if(archivo.fail()){ 
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
  	//Solicitamos los datos personales y los escribimos
	fflush(stdin);
	archivo<<"Cedula de identidad: "+nombreArchivo<<endl;
	cout<<"Digite sus nombres: ";
	getline(cin,info); archivo<<"Nombres: "+info<<endl;
	cout<<"Digite sus apellidos: ";
	getline(cin,info); archivo<<"Apellidos: "+info<<endl;
	//Guardamos la fecha de registro suministrada por el sistema
	const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%d-%m-%Y", localtime(&t));
  		
  	archivo<<"Fecha de registro: "<<endl;
	archivo<<s<<endl;
	
	archivo<<"--------------Historial de prestamos:------------"<<endl;
	 
	cout<<"\n\nRegistro exitoso!\n";
	system("pause");
	
	}
	//Cerramos el archivo
	archivo.close(); 
}

//Funcion que registra libros
void registrarLibro(){
	ofstream archivo;
	string nombreArchivo,nombreArchivom,info;
	char rpt;
	//Solicitamos su codigo
	fflush(stdin);
	cout<<"Digite el codigo del libro: ";
	getline(cin,nombreArchivo);
	//Establecemos el nombre de archivo unico
	nombreArchivom= ".//libros//"+nombreArchivo+".txt";
	//Comprobamos si existe la carpeta
	if (is_dir(nombreArchivom)){
	
	cout << "La carpeta existe" << endl;
	system("pause");
	//Comprobamos si existe un archivo para este libro
	} else if (is_file(nombreArchivom)){
		
		cout << "El archivo existe" << endl;
		system("pause");
	
	} else {
		//Creamos el archivo
		archivo.open(nombreArchivom.c_str(),ios::out);
  		//Si a ocurrido algun error
  		if(archivo.fail()){
			cout<<"No se pudo abrir el archivo";
			exit(1);
		}
		//Solicitamos los datos del libro y los escribimos
 		fflush(stdin);
		archivo<<"Codigo del libro: "+nombreArchivo<<endl;
		cout<<"Digite su titulo: ";
		getline(cin,info); archivo<<"Titulo: "+info<<endl;
		cout<<"Digite estado del libro: \n";
		cout<<"[1] Nuevo"<<endl;
		cout<<"[2] Excelente"<<endl;
		cout<<"[3] Bueno"<<endl;
		cout<<"[4] Degradado"<<endl;
		int op;
		cin>>op;
		switch(op){
			case 1: info = "nuevo"; break;
            case 2: info = "excelente"; break;
            case 3: info = "bueno"; break;
            case 4: info = "degradado"; break;
            default: cout<<"ERROR";
		}
	
		archivo<<"Estado del libro: "+info<<endl;
		
		archivo<<"--------------Historial de prestamos:------------"<<endl;
	
		cout<<"\n\nRegistro exitoso!\n";
		system("pause");
	}
	//Cerramos el archivo
	archivo.close(); 
}

//Funcion que registra prestamos en historial cliente
void clientePrestamo(){
	ofstream archivo;
	string nombreArchivo,nombreArchivom,info;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite nuevamente la cedula del cliente: ";
	getline(cin,nombreArchivo);
	
	nombreArchivom= ".//clientes//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){
		cout << "La carpeta existe" << endl;
		system("pause");
	} else if (is_file(nombreArchivom)){
		archivo.open(nombreArchivom.c_str(),ios::app);//Creamos el archivo
  
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
  	
	fflush(stdin);
  	
	archivo<<"Prestamo: "<<endl;
	
	const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%d-%m-%Y", localtime(&t));
  		
  	archivo<<"Fecha del Prestamo: "<<endl;
	archivo<<s<<endl;
	
	cout<<"Digite la fecha en que debe ser entregado: ";
	getline(cin,info); archivo<<"Fecha a entregar el libro: "+info<<endl;
	 
	cout<<"\n\nRegistro exitoso!\n";
	cout<<"Desea imprimir el historial de prestamo? (s/n)\n";
	
	cin>>rpt;
	
	if((rpt == 'S') || (rpt == 's')){
		// Identifica el puerto de la impresora
   char const * const  pszPrinterName = "LPT1:" ;

   // Abre el flujo de la impresora
   ofstream  prn( pszPrinterName );

   // Asegura que la impresora se abrio exitosamente
   if ( ! prn ) {
      cerr << "ERROR: No se puede abrir " << pszPrinterName << '\n' ;
      system("pause");
   }

   // Imprime un mensaje
   prn << nombreArchivom;

   prn << '\r'     // Retorno de carro (ENTER)
       << '\f' ;   // Expulsa la ultima hoja de la impresora

   // Cierra la impresora
   prn.close();
	}
	
	} else {
		
		cout<<"Cliente no existe\n";
		cout<<"Desea registrarlo? (s/n)\n";
	
		cin>>rpt;
	
		if((rpt == 'S') || (rpt == 's')){
			registrarCliente();
		}
	}

	archivo.close(); //Cerramos el archivo
}

//Funcion que registra prestamos en historial libro
void registrarPrestamo(){
	ofstream archivo;
	string nombreArchivo,nombreArchivom,info;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite el codigo del libro: ";
	getline(cin,nombreArchivo);
	
	nombreArchivom= ".//libros//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){
	
		cout << "La carpeta existe" << endl;
		system("pause");
	
	} else if (is_file(nombreArchivom)){
		
		archivo.open(nombreArchivom.c_str(),ios::app);//Creamos el archivo
   
	if(archivo.fail()){ //Si a ocurrido algun error
	
		cout<<"No se pudo abrir el archivo";
		exit(1);
	
	}
	
	archivo<<"Prestamo: "<<endl;
	cout<<"Digite la cedula del cliente: ";
	getline(cin,info); archivo<<"En estatus de prestamo al cliente: "+info<<endl;
	
	clientePrestamo();
	
  } else {
		cout<<"Libro no existe\n";
		cout<<"Desea registrarlo? (s/n)\n";
	
		cin>>rpt;
	
		if((rpt == 'S') || (rpt == 's')){
			registrarLibro();
		}
	}

	archivo.close(); //Cerramos el archivo
}

//Funcion que registra penalizacion en caso de entrega tardia
void penalizacion(){
	ofstream archivo;
	string nombreArchivo,nombreArchivom,info;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite nuevamente la cedula del cliente: ";
	getline(cin,nombreArchivo);
	
	nombreArchivom= ".//clientes//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){
		cout << "La carpeta existe" << endl;
		system("pause");
	} else if (is_file(nombreArchivom)){
		archivo.open(nombreArchivom.c_str(),ios::app);//Creamos el archivo
  
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
  	
	fflush(stdin);

	cout<<"Digite los dias de retraso: ";
	getline(cin,info);
	
	cout<<"Debera cancelar: "<<info<<"$ \n";
	cout<<"Cancelado? (s/n) \n"<<endl;
	cin>>rpt;
	
	if((rpt == 'S') || (rpt == 's')){
		archivo<<"-------------------Penalizado y ENTREGADO-------------------------------"<<endl;
		cout<<"\n\nRegistro exitoso!\n";
		system("pause");
	} else {
		cout<<"Debe pagar su multa para poder disfrutar de nuestros servicios"<<endl;
		system("pause");
	}
	
	} else {	
		cout<<"Cliente no existe\n";
		system("pause");
	}

	archivo.close(); //Cerramos el archivo
	
}

//Funcion que escribe estaus de entrega en historial
void clienteEntregaW(){
	ofstream archivo;
	string nombreArchivo,nombreArchivom,info;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite nuevamente la cedula del cliente: ";
	getline(cin,nombreArchivo);
	
	nombreArchivom= ".//clientes//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){
		cout << "La carpeta existe" << endl;
		system("pause");
	} else if (is_file(nombreArchivom)){
		archivo.open(nombreArchivom.c_str(),ios::app);//Creamos el archivo
  
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
  	
	fflush(stdin);
	
	const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%d-%m-%Y", localtime(&t));
	
	int dia_aux, anio_aux, mes_aux;
    Fecha diaA(31,12,2200), diaB(1,1,0);
 
    cout<< "Copie y pegar fecha en que debe o debio ser entregado: ";
    diaA.scanfecha();
    cout<<s;
    cout<<"\nFavor copiar y pegar la fecha actual: ";
    diaB.scanfecha();
    
    if(dif_dias(diaA,diaB)>1){
    	fflush(stdin);
    	cout << endl << "PENALIZADO \n";
    	cout << endl << "DIAS DE RETRASO: "<<dif_dias(diaA,diaB)<<"\n\n";
    	penalizacion();
	} else {
		
		cout<<"Digite estado del libro: \n";
		cout<<"[1] Nuevo"<<endl;
		cout<<"[2] Excelente"<<endl;
		cout<<"[3] Bueno"<<endl;
		cout<<"[4] Degradado"<<endl;
		int op;
		cin>>op;
		switch(op){
			case 1: info = "nuevo"; break;
            case 2: info = "excelente"; break;
            case 3: info = "bueno"; break;
            case 4: info = "degradado"; break;
            default: cout<<"ERROR";
		}
	
		archivo<<"Estado del libro: "+info<<endl;
		archivo<<"-----------------------ENTREGADO---------------------------"<<endl;
	 
		cout<<"\n\nEntrega exitosa!\n";
		system("pause");
	}
		
	} else {
		
		cout<<"Cliente no existe\n";
	}

	archivo.close(); //Cerramos el archivo
}

//Funcion que registra entrega en historial cliente
void clienteEntrega(){
	ifstream archivo;
	string nombreArchivo,nombreArchivom,texto;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite la cedula del cliente: ";
	getline(cin,nombreArchivo);
	
	cout<<"\n\n";
	nombreArchivom= ".//clientes//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){
		cout << "La carpeta existe" << endl;
		system("pause");
	} else if (is_file(nombreArchivom)){
  
	archivo.open(nombreArchivom.c_str(),ios::in);
  
		if(archivo.fail()){ //Si a ocurrido algun error
			cout<<"No se pudo abrir el archivo";
			exit(1);
		}
  
		while(!archivo.eof()){ //mientras no sea final del archivo
			getline(archivo,texto);
			cout<<texto<<endl;
		}
	} else {
  		cout << "El cliente no existe" << endl;
		system("pause");
	}
  	
	archivo.close(); //Cerramos el archivo
	
	clienteEntregaW();
}

//Funcion que registra entrega en historial libro
void registrarEntrega(){
	ofstream archivo;
	string nombreArchivo,nombreArchivom,info;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite el codigo del libro: ";
	getline(cin,nombreArchivo);
	
	nombreArchivom= ".//libros//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){
	
		cout << "La carpeta existe" << endl;
		system("pause");
	
	} else if (is_file(nombreArchivom)){
		
		archivo.open(nombreArchivom.c_str(),ios::app);//Creamos el archivo
   
	if(archivo.fail()){ //Si a ocurrido algun error
	
		cout<<"No se pudo abrir el archivo";
		exit(1);
	
	}
	
	archivo<<"-----------------------ENTREGADO---------------------------"<<endl;
	
	clienteEntrega();
	
  } else {
		cout<<"Libro no existe\n";
		system("pause");
	}

	archivo.close(); //Cerramos el archivo
}

//Funcion que elimina cliente
void eliminarCliente(){
	string nombreArchivo;
	
	fflush(stdin);
	cout<<"Digite la cedula del cliente: ";
	getline(cin,nombreArchivo);
	
	nombreArchivo= ".//clientes//"+nombreArchivo+".txt";
	
	remove(nombreArchivo.c_str());
	
	cout<<"\n\nEliminado! \n";
	system("pause");
}

//Funcion que elimina libro
void eliminarLibro(){
	string nombreArchivo;
	
	fflush(stdin);
	cout<<"Digite el codigo del libro: ";
	getline(cin,nombreArchivo);
	
	nombreArchivo= ".//libros//"+nombreArchivo+".txt";
	
	remove(nombreArchivo.c_str());
	
	cout<<"\n\nEliminado! \n";
	system("pause");
}

//Funcion que verifica cliente y muestra historial
void verificarCliente(){
	ifstream archivo;
	string nombreArchivo,nombreArchivom,texto;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite la cedula del cliente: ";
	getline(cin,nombreArchivo);
	cout<<"\n\n";
	
	nombreArchivom= ".//clientes//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){
		cout << "La carpeta existe" << endl;
		system("pause");
	} else if (is_file(nombreArchivom)){
  
	archivo.open(nombreArchivom.c_str(),ios::in);
  
		if(archivo.fail()){ //Si a ocurrido algun error
			cout<<"No se pudo abrir el archivo";
			exit(1);
		}
  
		while(!archivo.eof()){ //mientras no sea final del archivo
			getline(archivo,texto);
			cout<<texto<<endl;
		}
		
		system("pause");
	} else {
  		cout << "El cliente no existe" << endl;
		system("pause");
	}
  	
	archivo.close(); //Cerramos el archivo
}

//Funcion que verifica libro y muestra historial
void verificarLibro(){
	ifstream archivo;
	string nombreArchivo,nombreArchivom,texto;
	char rpt;
	
	fflush(stdin);
	cout<<"Digite el codigo del libro: ";
	getline(cin,nombreArchivo);
	cout<<"\n\n";
	
	nombreArchivom= ".//libros//"+nombreArchivo+".txt";
	
	if (is_dir(nombreArchivom)){	
		cout << "La carpeta existe" << endl;
		system("pause");
  
	} else if (is_file(nombreArchivom)){
		
		archivo.open(nombreArchivom.c_str(),ios::in);
  
		if(archivo.fail()){ //Si a ocurrido algun error
			cout<<"No se pudo abrir el archivo";
			exit(1);
		}
  
		while(!archivo.eof()){ //mientras no sea final del archivo
			getline(archivo,texto);
			cout<<texto<<endl;
		}
		system("pause");
  		
		} else {		
			cout << "El libro no existe" << endl;
  			system("pause");
  }
  	
	archivo.close(); //Cerramos el archivo
}

//Funcion que muestra la informacion de la biblioteca
void acercade(){
	ifstream archivo;
	string texto;
	
	archivo.open(".//informacion//acercade.txt",ios::in); //Abrimos el archivo en modo lectura
	
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	while(!archivo.eof()){ //mientras no sea final del archivo
		getline(archivo,texto);
		cout<<texto<<endl;
	}
	
	system("pause");
	
	archivo.close(); //Cerramos el archivo
}

//Declaraciones de los diferentes menus
int menuPrincipal();
int prestamosEntregas();
int clientes();
int libros();

//Menu y submenus
int main(int argc, char *argv[]) {
int opmenu=0;

do {
	opmenu=menuPrincipal();
	switch (opmenu) {
	case 1:
		{
		int opprestamosEntregas=0;
		do {
			opprestamosEntregas=prestamosEntregas();
			switch (opprestamosEntregas) {
			case 1:
				registrarPrestamo();
				break;
			case 2:
				registrarEntrega();
				break;
			default:
				cout<<"Cargando..."<<endl;
				};
			} while (opprestamosEntregas!=3);
		}
		break;
	case 2:
		{
		int opclientes=0;
		do {
			opclientes=clientes();
			switch (opclientes) {
			case 1:
				registrarCliente();
				break;
			case 2:
				verificarCliente();
				break;
			case 3:
				eliminarCliente();
				break;
			default:
				cout<<"Cargando..."<<endl;
				};
			} while (opclientes!=4);
		}
			break;
		case 3:	
		{
		int oplibros=0;
		do {
			oplibros=libros();
			switch (oplibros) {
			case 1:
				registrarLibro();
				break;
			case 2:
				verificarLibro();
				break;
			case 3:
				eliminarLibro();
				break;
			default:
				cout<<"Cargando..."<<endl;
				};
			} while (oplibros!=4);
		}
				break;
			case 4:
				acercade();
				break;
		default:
			cout<<"Cargando..."<<endl;
			};
		} while (opmenu!=5);
		return 0;
}

//Pantalla del menu principal
int menuPrincipal() {
	
	system("color F0");
	system("cls");
	
	ifstream archivo;
	string texto;
	
	archivo.open(".//informacion//bibliotecaPSM.txt",ios::in); //Abrimos el archivo en modo lectura
	
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	while(!archivo.eof()){ //mientras no sea final del archivo
		getline(archivo,texto);
		cout<<texto<<endl;
	}
	
	archivo.close(); //Cerramos el archivo

	cout<<"\n\n";
	cout<<"                                 [1] Prestamo de libros"<<endl;
	cout<<"                                 [2] Administracion de clientes"<<endl;
	cout<<"                                 [3] Administracion de libros"<<endl;
	cout<<"                                 [4] Acerca de la biblioteca PSM"<<endl;
	cout<<"                                 [5] Salir \n"<<endl;
	
	cout<<"                                 Ingrese una opcion y presione enter:  ";
	int opmenu;
	cin>>opmenu;
	cout<<"\n\n\n";
	
	return opmenu;
}

//Pantalla del menu para prestamos y entregas
int prestamosEntregas() {
	system("cls");
	
	cout<<"\n\n\n\n\n\n\n\n";
	cout<<"                                 [1] Registrar Prestamo"<<endl;
	cout<<"                                 [2] Registrar Entrega"<<endl;
	cout<<"                                 [3] Regresar al menu de inicio"<<endl;
	
	cout<<"                                 Ingrese una opcion y presione enter:  ";
	int opprestamosEntregas;
	cin>>opprestamosEntregas;
	
	return opprestamosEntregas;
}

//Pantalla del menu para clientes
int clientes() {
	system("cls");
	
	cout<<"\n\n\n\n\n\n\n\n";
	cout<<"                                 [1] Registrar cliente"<<endl;
	cout<<"                                 [2] Verificar cliente y su historial"<<endl;
	cout<<"                                 [3] Eliminar cliente y su historial"<<endl;
	cout<<"                                 [4] Regresar al menu de inicio"<<endl;
	
	cout<<"                                 Ingrese una opcion y presione enter:  ";
	int opclientes;
	cin>>opclientes;
	
	return opclientes;
}

//Pantalla del menu para libros
int libros() {
	system("cls");
	
	cout<<"\n\n\n\n\n\n\n\n";
	cout<<"                                 [1] Registrar libro"<<endl;
	cout<<"                                 [2] Verificar libro y su historial"<<endl;
	cout<<"                                 [4] Eliminar libro y su historial"<<endl;
	cout<<"                                 [4] Regresar al menu de inicio"<<endl;
	
	cout<<"                                 Ingrese una opcion y presione enter:  ";
	int oplibros;
	cin>>oplibros;
	
	return oplibros;
}

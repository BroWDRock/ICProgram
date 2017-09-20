#include <iostream>
#include <fstream>
#include <sys/resource.h>
#include <string>
#include <math.h>
using namespace std;

long double tiempo(){
	struct rusage usage;
	getrusage(RUSAGE_SELF,&usage);
	return( (long double) usage.ru_utime.tv_sec +
		(long double) usage.ru_utime.tv_usec/1e6);
}

string denc1(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	val=st[i];
	  if (val>32){
		val=val-4;
		if(val<33){
			val=val+165-33;
		}
	  }
	  st[i]=val;
	}
    cout << st << endl;
	return st;
}

string enc1(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	val=st[i];
	  if (val>32){
		val=val+4;
		if(val>165){
			val=val-165+32;
		}
	  }
	  st[i]=val;
	}
    cout << st << endl;
	return st;
}

string denc2(string st){
	int i;
	int val;
	long long int aux;
	for(i=0;i<st.length();i++){
		val=st[i]-32;
	  if(val<33){
		aux=(pow(val,7));
		st[i]=aux%33+32;
	  }else if(val<66){
		aux=(pow(val-33,7));
		st[i]=aux%33+32+33;
	  }else if(val<99){
		aux=(pow(val-66,7));
		st[i]=aux%33+32+66;
	  }else{
		aux=(pow(val-99,7));
		st[i]=aux%33+32+99;
	  }
	}
    cout << st << endl;
	return st;
}

string enc2(string st){
	int i;
	int val;
	long long int aux;
	for(i=0;i<st.length();i++){
	  val=st[i]-32;
	  if(val<33){
		aux=(pow(val,3));
		st[i]=aux%33+32;
	  }else if(val<66){
		aux=(pow(val-33,3));
		st[i]=aux%33+32+33;
	  }else if(val<99){
		aux=(pow(val-66,3));
		st[i]=aux%33+32+66;
	  }else{
		aux=(pow(val-99,3));
		st[i]=aux%33+32+99;
	  }
	}
        cout << st << endl;
	denc2(st);
	return st;
}

string denc3(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	  if(st[i]>32){
		val=st[i]-32;
		val=46*(val-3)%91;
		if(val<0){
		  val=91+val;
		}
		st[i]=val+32;
	  }
	}
    
    cout << st << endl;
	return st;
}

string enc3(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	  if(st[i]>32){
		val=st[i]-32;		
		val=(2*val+3)%91;
		st[i]=val+32;
	  }
	}
    
    cout << st << endl;
	return st;
}

void leerFichero(char eleccion)
{
    ifstream f;
    fstream fich;
    string leer;
    string nombreFichero = "fichero.txt";
    string nombre="resultado.txt";
    fich.open(nombre.c_str(),ios::out);
    //comprobamos que no se haya introducido el nombre del fichero
    if(nombreFichero == "")
    {
        cout << "Filename: ";
        getline(cin, nombreFichero);
    }
    
    f.open(nombreFichero.c_str());//abrimos el fichero
    
    if(f.is_open() && fich.is_open())
    {
        do
        {
            if(eleccion == '1')
            {
                getline(f, leer);
                
                fich<<enc1(leer)<<endl;
            }
            else if(eleccion == '2')
            {
                getline(f, leer);
                 fich<<enc2(leer)<<endl;
            }
            else if(eleccion == '3')
            {
                getline(f, leer);
                 fich<<enc3(leer)<<endl;
            }
            else
            {
                cout << "\nCagada Monumental" << endl;
            }
            
        } while(f.eof()==false);
        
        f.close();//Cerramos el fichero
        fich.close();
    }
    else
    {
        cout << "Error. Can't open file.";
    }
}

void encriptar()
{
    char op;
    char eleccion;
    do
    {
        cout << "\nWhich type of encrypt do you want?" << endl;
        cout << "Type 1" << endl;
        cout << "Type 2" << endl;
        cout << "Type 3\n" << endl;
        cout << "Select: ";
    
        cin >> op;
        
        cout << endl;
        
        switch(op)
        {
            case '1':
                leerFichero(op);
                
                break;
                
            case '2':
                leerFichero('2');
                
                break;
                
            case '3':
                leerFichero('3');
                break;
                
            default: cout << "\nError. Option not valid.\n" << endl;
        }
        
    } while(op != '1' && op != '2' && op != '3');
}

void desencriptar()
{

}

void menu()
{
    long double t_inicial, t_final, t_ejecucion;
    char op;
     string nuevo;
    
    do {
        cout << "\n1. Encrypt file." << endl;
        cout << "2. Decrypt file." << endl;
        cout << "3. Exit.\n" << endl;
        
        cout << "Select option: ";
        cin >> op;
        
        switch(op) {
                
            case '1':
                t_inicial = tiempo();
                // Llamada a la función de encriptación.
                encriptar();
                t_final = tiempo();
                
                cout << "Time needed to encrypt the file: " << t_final - t_inicial << " s" << endl;
                
                break;
                
            case '2':
                t_inicial = tiempo();
                // Llamada a la función de desencriptación.
                desencriptar();
                t_final = tiempo();
                
                cout << "Time needed to decrypt the file: " << t_final - t_inicial << " s" << endl;
                
                break;
                
            case '3':
                cout << "The program has ended." << endl;
                break;
                
                
            default: cout << "\nError. Option not valid.\n" << endl;
        }
        
    } while(op != '3');
}

int main()
{
    menu();
    
}

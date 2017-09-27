#include <iostream>
#include <fstream>
#include <sys/resource.h>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

string INPUT, OUTPUT;

const string ENCRYPT_TIME = "Time needed to encrypt the file: ";
const string DECRYPT_TIME = "Time needed to decrypt the file: ";

long double tiempo(){
	struct rusage usage;
	getrusage(RUSAGE_SELF,&usage);
	return( (long double) usage.ru_utime.tv_sec +
		(long double) usage.ru_utime.tv_usec/1e6);
}

long long int ex29(int n){
  long long int aux,aux2;
  aux2=(int)pow(n,4)%91;
  aux=(int)pow(aux2,4)%91;
  aux=aux*aux2*aux2*aux2%91;
  aux=aux*n%91;
  return aux;
}

string denc1(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	val=st[i];
	  if (val>32){
		val=val-4;
		if(val<33){
			val=val+126-33;
		}
	  }
	  st[i]=val;
	}
	return st;
}

string enc1(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	val=st[i];
	  if (val>32){
		val=val+4;
		if(val>126){
			val=val-126+32;
		}
	  }
	  st[i]=val;
	}
	return st;
}

string denc2(string st){
	int i;
	int val;
	long long int aux;
	for(i=0;i<st.length();i++){
	  if(st[i]>32){	
	    val=st[i]-32;
	    st[i]=ex29(val)%91+32;	

	  }
	}
	return st;
}

string enc2(string st){
	int i;
	int val;
	long long int aux;
	for(i=0;i<st.length();i++){
	  if(st[i]>32){
	    val=st[i]-32;
	    aux=pow(val,5);
 	    st[i]=aux%91+32;
	  }	  
	}
	return st;
}

string denc3(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	  if(st[i]>32){
		val=st[i]-33;
		val=47*(val-3)%93;
		if(val<0){
		  val=93+val;
		}
		st[i]=val+33;
	  }
	}
	return st;
}

string enc3(string st){
	int i;
	int val;
	for(i=0;i<st.length();i++){
	  if(st[i]>32){
		val=st[i]-33;		
		val=(2*val+3)%93;
		st[i]=val+33;
	  }
	}
	return st;
}

void escribir(vector<string> texto){
   fstream fich;
   fich.open(OUTPUT.c_str() , ios::out);
   
   if(fich.is_open()){
    for(int i=0; i<texto.size(); i++){
        fich<<texto[i];
        fich<<"\n";
    }
       
   }

   fich.close();
}

bool leerFichero(char eleccion)
{
    ifstream f;

    bool leido = false;
   
    string leer="";
    string linea="";
    vector<string> concatenado;
    
    f.open(INPUT.c_str());//abrimos el fichero

    if(f.is_open())
    {
       getline(f, leer);
        while(!f.eof()){
            
            if(eleccion == '1')
            {
               linea=enc1(leer);
               
            }
            else if(eleccion == '2')
            {
                linea=enc2(leer);
            }
            else if(eleccion == '3')
            {
                 linea=enc3(leer);
            }else if(eleccion == '4')
            {
                linea=denc1(leer);
            }else if(eleccion == '5')
            {
                linea=denc2(leer);
            }else if(eleccion == '6')
            {
                linea=denc3(leer);
            }
            else
            {
                cout << "\nCagada Monumental" << endl;
            }
            concatenado.push_back(linea);
            getline(f, leer);
            linea="";
       
        }
         f.close();//Cerramos el fichero
         escribir(concatenado);

         leido = true;
    }
    else
    {
        cout << "Error. Can't open file." << endl;
    }

    return leido;
}

void menu(char op)
{
    long double t_inicial, t_final;
    string nuevo;
    bool leido;
    
    switch(op) {
            
        case '1':
            t_inicial = tiempo();
            leido = leerFichero(op);
            t_final = tiempo();

            if(leido == true) {
                cout << ENCRYPT_TIME << t_final - t_inicial << " s" << endl;
            }

            return;
        break;
                
        case '2':
            t_inicial = tiempo();
            leido = leerFichero(op);
            t_final = tiempo();

            if(leido == true) {
                cout << ENCRYPT_TIME << t_final - t_inicial << " s" << endl;
            }

            return;
        break;
                
        case '3':
            t_inicial = tiempo();
            leido = leerFichero(op);
            t_final = tiempo();

            if(leido == true) {
                cout << ENCRYPT_TIME << t_final - t_inicial << " s" << endl;
            }

            return;
        break;

        case '4':
            t_inicial = tiempo();
            leido = leerFichero(op);
            t_final = tiempo();

            if(leido == true) {
                cout << DECRYPT_TIME << t_final - t_inicial << " s" << endl;
            }

            return;
        break;
                
        case '5':
            t_inicial = tiempo();
            leido = leerFichero(op);
            t_final = tiempo();

            if(leido == true) {
                cout << DECRYPT_TIME << t_final - t_inicial << " s" << endl;
            }

            return;
        break;
                
        case '6':
            t_inicial = tiempo();
            leido = leerFichero(op);
            t_final = tiempo();

            if(leido == true) {
                cout << DECRYPT_TIME << t_final - t_inicial << " s" << endl;
            }

            return;
        break;
                
        default: cout << "Error. Option not valid." << endl;
            return;
       
    } while(op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6');
}

int main(int argc, char *argv[]) {

    if(argc != 4) {
        cout << "Syntax Error." << endl;
        cout << "Correct syntax: <executable> <input_filename> <output_filename> <option>" << endl;

        cout << "\nOPTIONS:\n" << endl;

        cout << "1. Encription type 1" << endl;
        cout << "2. Encription type 2" << endl;
        cout << "3. Encription type 3" << endl;
        cout << endl;

        cout << "4. Decription type 1" << endl;
        cout << "5. Decription type 2" << endl;
        cout << "6. Decription type 3\n" << endl;
    }
    else {
        INPUT = argv[1];
        OUTPUT = argv[2];
        char opt = (char) *argv[3];

        menu(opt);
    }
}

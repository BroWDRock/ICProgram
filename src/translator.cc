#include <iostream>
#include <fstream>
#include <sys/resource.h>
#include <string>
#include <math.h>
#include <omp.h>
#include <vector>

using namespace std;


//constantes de mpi
#define MAX_PROCESSES 10




const string ERROR_FICH = "Error. Can't open file.";

long double tiempo(){
	struct rusage usage;
	getrusage(RUSAGE_SELF,&usage);
	return( (long double) usage.ru_utime.tv_sec +
		(long double) usage.ru_utime.tv_usec/1e6);
}

int numberlines(string indice){
    int lineas = 0;
    ifstream fich;
    string aux;
    fich.open(indice.c_str());
    if(fich.is_open()){
        while(fich.eof() == false){
            getline(fich, aux);
            lineas++;
        }
    }
    fich.close();
    return lineas;
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
	string nuevo;

	 #pragma omp simd
	for(i=0;i<st.length();i++){
	val=st[i];
	  if (val>32){
		val=val-4;
		if(val<33){
			val=val+126-33;
		}
	  }
	  nuevo+=val;
	}
	return nuevo;
}

string enc1(string st){
	int i;
	int val;
	#pragma omp simd
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
	#pragma omp simd
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
	#pragma omp simd
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
	#pragma omp simd
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
	#pragma omp simd
	for(i=0;i<st.length();i++){
	  if(st[i]>32){
		val=st[i]-33;		
		val=(2*val+3)%93;
		st[i]=val+33;
	  }
	}
	return st;
}

void escribir(vector<string> texto, string out){
   fstream fich;
   fich.open(out.c_str() , ios::out);
   
   if(fich.is_open()){
    
    for(int i=0; i<texto.size(); i++){
        fich<<texto[i];
        fich<<"\n";
    }
       
   }

   fich.close();
}

//------------------------------------------------------------------- metodo de mpi
bool leerFichero(string eleccion, string in, string out)
{
    ifstream f;

    bool leido = false;
   
    string leer="";
    string linea;
    f.open(in.c_str());
    
    char caracteres[1000][200];  // 1000 lineas de 200 caracteres
    int contador=0;             // contador de lineas 

    if(f.is_open())
    {
       getline(f, leer);
       
       for(int j=0; j<leer.size(); j++){   // for para cada linea a caracteres
        caracteres[contador][j]=leer[j];
       }
   
        while(!f.eof()){
            contador++;         // aumento las lineas
            getline(f, leer);      //leo la siguente linea
           
            
        for(int j=0; j<leer.size(); j++){   // for para cada linea a caracteres
            caracteres[contador][j]=leer[j];
        }
       
        }
         f.close();
         
         //ahora tengo un vector de caracteres [linea(num)] [caracteres de la linea]
         
         //ahora va el scatter
         
         //despues el if infinito ese 
         
         // despues el gather
         
         //escribir(concatenado, out);

         leido = true;
    }
    else
    {
        cout << ERROR_FICH << endl;
    }

    return leido;
}


//--------------------------------------------------------------------------------fin mpi metodo
/*
void procesarLinea(string linea, string input, string output){
    int i=0;
    char opc;

    while(i<linea.length()){

        while(i<linea.length() && linea[i]!=' '){
            input+=linea[i];
            i++;
        }
        
        i++;

        while(i<linea.length() && linea[i]!=' '){
            output+=linea[i];
            i++;
        }
        
        i++;

        opc=linea[i];

        i++;
    }

    leerFichero(opc, input, output);
}
*/

/*
void procesarFichero(string input, string output, char op){
    ifstream fich;
    string linea, in="", out="";
    int chunksize, tid;
    vector<string> lineas;

    chunksize = numberlines(input);
    fich.open(input.c_str());
      if (fich.is_open()){

        for(int i = 0; i < chunksize; i++)
        {
            getline(fich, linea);
            lineas.push_back(linea);
            
        }
    }
    
    if(fich.is_open())
    {
        #pragma omp parallel for num_threads(chunksize) private(in, out, linea)
            for(int x=0; x<lineas.size()-1; x++){
                linea = lineas[x];

                #pragma omp parallel
                {
                leerFichero(op, input, output);
                }
            }
    }   
}
*/

int main(int argc, char *argv[]) {
    long double t_inicial, t_final;
    
    // Setup MPI
    MPI_Init( &argc, &argv ); //-------------------------------- inicio mpi
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    if(argc != 4) {
        cout << "Syntax Error." << endl;
        cout << "Correct syntax: <executable> <input_file> <output_file> option" << endl;
    }
    else {
        string input = argv[1];
        string output = argv[2];
        string op = argv[3];

        t_inicial = tiempo();
        leerFichero(op, input, output);
        t_final = tiempo();

        cout << "Time: " << t_final - t_inicial << " s" << endl;
    }
          MPI_Finalize(); ////////////////////////////---- fin de mpi
}

/*
int main(int argc, char *argv[]) {
    long double t_inicial, t_final;

    if(argc != 2) {
        cout << "Syntax Error." << endl;
        cout << "Correct syntax: <executable> <index_file>" << endl;
    }
    else {
        string index = argv[1];

        t_inicial = tiempo();º
        procesarFichero(index);
        t_final = tiempo();

        cout << "Time: " << t_final - t_inicial << " s" << endl;
    }
}
*/




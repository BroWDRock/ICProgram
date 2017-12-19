#include <iostream>
#include <fstream>
#include <sys/resource.h>
#include <string>
#include <math.h>
#include <omp.h>
#include <vector>
#include "mpi.h"
using namespace std;


//variables globales MPI
int rank;
int size;
int numCaracteresLinea=200;
int maxLineas=1000;

#define MAX_PROCESSES 0
//------------------------------

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


const char * denc1(string st){
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
    const char * r = nuevo.c_str();
    return r;
}

const char * enc1(string st){
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
    const char * r = st.c_str();
    return r;
}

const char * denc2(string st){
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
    const char * r = st.c_str();
    return r;
}

const char * enc2(string st){
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
    const char * r = st.c_str();
    return r;
}

const char * denc3(string st){
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
  const char * r = st.c_str();
    return r;
}

const char * enc3(string st){
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
  const char * r = st.c_str();
    return r;
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
    int participants; //NUMERO DE PARTICIPANTES EN LOS QUE DIVIDIR el algoritmo
    string leer="";
    f.open(in.c_str());
    
    
    char caracteres[maxLineas][numCaracteresLinea];  // 1000 lineas de 200 caracteres
    char linea[numCaracteresLinea];                  //linea
    int contador=0;             // contador de lineas 

     // Setup MPI
    MPI_Init( NULL, NULL ); //-------------------------------- inicio mpi // podria ponerlo en el main igual pero seguia dando error asi que acote el error
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    
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
       
        } //fin de leer el fich
    
         f.close();
         
         //ahora tengo un vector de caracteres [linea(num)] [caracteres de la linea]
         
         //------------------------------------------------------------------------------------
            
        if ( size > MAX_PROCESSES ) 
            participants = MAX_PROCESSES;
        else 
            participants = size;
        
        if ( (rank < participants) )    {
        int send_count = MAX_PROCESSES;
        int recv_count = MAX_PROCESSES;
 
        /* si no soy root (process 0), entonces encript o lo que sea */
        //no hace falta xk la matriz ya esta hecha 

        /* pasar la matriz a cada proceso una linea char[200] */
        MPI_Scatter(&caracteres[0][0], send_count, MPI_CHAR, 
                         &linea[0] , recv_count, MPI_CHAR, 0, MPI_COMM_WORLD);
        
          if(eleccion == "1")
            {
               //linea=enc1(leer);
            }
            else if(eleccion == "2")
            {
                //linea=enc2(leer);
            }
            else if(eleccion == "3")
            {
                 //linea=enc3(leer);
            }else if(eleccion == "4")
            {
                //linea=denc1(leer);
            }else if(eleccion == "5")
            {
                //linea=denc2(leer);
            }else if(eleccion == "6")
            {
                //linea=denc3(leer);
            }
            else
            {
                cout << "\nCagada Monumental" << endl;
            } 
           
            MPI_Gather(&linea, recv_count, MPI_CHAR, &caracteres[0][0], send_count, MPI_CHAR, 0, MPI_COMM_WORLD);
           
           /* 
            MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Gather(&localdata, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);
            */
        
        }
 MPI_Finalize(); ////////////////////////////---- fin de mpi
        //-------------------------------------------------------------------------------------------------------
       
         leido = true;
    }
    else
    {
        cout << ERROR_FICH << endl;
    }

    return leido;
}





int main(int argc, char *argv[]) {
    long double t_inicial, t_final;
    
   
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
          
}





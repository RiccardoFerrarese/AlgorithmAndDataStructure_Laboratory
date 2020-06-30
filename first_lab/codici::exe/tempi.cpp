//
// Created by Riccardo Ferrarese on 07/11/2019.
//
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <sstream>
using namespace std;


struct tempi{
    double tTot;
    double tMedio;
}typedef Tempi;

struct misurazioni{
    double e;
    double delta;
    double sd; 
}typedef MisurazioniT;


float granularita();
int calcolaRip( float tMin, char* batteria, int key, string exe);
Tempi calcoloTempi(char* batteria, int rip , int key, string exe);
int calcolaRipPrepara( float tMin, char* batteria, int key, string exe);
void launchExe(char*, int, string exe);
void prepara( char* batteria, string exe );
Tempi tempoMedioNetto( float tMin, char* batteria, int, string exe);
MisurazioniT misurazione(char* batteria, int dim, int key, int c, double za, float tMin, double delta, string exe );

template <typename T>               // consumes a line of input stream and converts it into a vector
istream &operator >> (istream &in, vector<T> &vec) {
    string line;
    getline(cin, line);              // read entire line from input stream
    istringstream s(line);          // create new stream from line
    
    int value;
    while (s >> value)              // turn line stream into vector
        vec.push_back(value);
    return in;
}

//template <typename T>               // concerts a vector into a line of output stream
ostream &operator << (ostream &out, const vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++)
        out << vec[i] << " ";
    out << endl;
    return out;
}
// funzioni di supporto
void parseInt(char* in){

    string line = (string)in; 
    vector<int> vec; 
    istringstream s(line);          // create new stream from line
    
    int value;
    while (s >> value)              // turn line stream into vector
        vec.push_back(value);
}

int standar_deviation( vector<double> vec ){

    int dim = vec.size(); 
    float sum = 0.0, mean, variance = 0.0, stdDeviation;

    int i;
    for(i = 0; i < dim; ++i)
        sum += vec[i];

    mean = sum/vec.size();

    for(i = 0; i < dim; ++i)
        variance += pow(vec[i] - mean, 2);

    variance=variance/5;
     return stdDeviation = sqrt(variance);
}

/// TUTTI I TEMPI RITORNATI DALLE FUNZIONI SONO IN SECONDI

float granularita(){

    //cout << "...calcolo granularità" << endl;
    float t0 = clock();
    float t1 = clock();

    while( t1 == t0){
        t1 = clock();
    }
    return (t1-t0)/CLOCKS_PER_SEC;
}

int calcolaRip( float tMin, char* batteria, int key, string exe){

    //cout << "...calcolo ripetizioni" << endl;
    float t0 = 0, t1 = 0;
    int rip = 1;

    while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
        rip = rip*2;             // stima rip con crescita esponenziale
        t0 = clock();

        for( int i = 0; i < rip; i++) {

            launchExe( batteria, key, exe );
        }

        t1 = clock();
    }

    int max = rip;
    int min = rip/2;
    int cicliErrati = 5;

    while( max - min >= cicliErrati ){
        rip = (max+min)/2;              // valore mediano
        t0 = clock();
        for( int i = 0; i < rip; i++) {

            launchExe( batteria, key, exe );

        }
        t1 = clock();
        float diff = (t1 - t0)/CLOCKS_PER_SEC;
        if( diff <= tMin){
            min = rip;
        } else {
            max = rip;
        }
    }

    return max;
}


Tempi calcoloTempi( char *batteria, int rip , int key, string exe){

    Tempi t;
    //batteria = generateWithDim( dim );


    float t0 = clock();
    for( int i = 0; i < rip; i++){

        //char* batteria = prepara( dim );
        launchExe( batteria , key, exe);
    }
    float t1= clock();
    float tTot = (t1-t0)/CLOCKS_PER_SEC;
    float tMed = tTot/rip;

    t.tTot = tTot;
    t.tMedio = tMed;
    //cout << "t medio: " << t.tMedio << "  t tot: " << t.tTot << endl;

    return t;
}

void launchExe( char* batteria, int k, string exe ){

    
    std::ostringstream ostr; //output string stream
    ostr << k;

    string str = ostr.str();
    char* key = (char*)str.c_str(); 

    char *data[] = {(char *) "/Users/riccardo/Desktop/ASD_vs/uno", batteria, key, (char*)0};

    pid_t pid = fork();

    if( pid == 0 ){
        //cout << "...... lancio algoritmo ......" << endl;
        if( (execv("/Users/riccardo/Desktop/ASD_vs/uno", data )) < 0 ){
        //cout<<"fine execv"<<endl;
            perror("execv failed");
        }

    } else if( pid > 0 ){
        wait( NULL );
    } else {
        perror("fork failed");
    }
}

// procedura per scorporare lettura dell'input dall'esecuzione dell'algoritmo
void prepara( char* batteria ){

    //char* batteria = generateWithDim( dim );
    //cout << endl << batteria << endl ;
    parseInt( batteria );
    //return batteria;

}


// PROCEDURE PER IL CALCOLO DEL TEMPO MEDIO CON PREPARAZIONE DELL'INPUT
int calcolaRipPrepara( float tMin, char* batteria, int key, string exe){

    float t0 = 0, t1 = 0;
    int rip = 1;


    while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
        rip = rip*2;             // stima rip con crescita esponenziale
        t0 = clock();

        for( int i = 0; i < rip; i++) {
            prepara( batteria );
        }

        t1 = clock();
    }


    int max = rip;
    int min = rip/2;
    int cicliErrati = 5;

    while( max - min >= cicliErrati ){
        rip = (max+min)/2;              // valore mediano
        t0 = clock();
        for( int i = 0; i < rip; i++) {
 
            prepara( batteria );
            launchExe( batteria, key , exe);
        }
        t1 = clock();
        float diff = (t1 - t0)/CLOCKS_PER_SEC;
        if( diff <= tMin){
            min = rip;
        } else {
            max = rip;
        }
    }
    return max;
}

/**
 * Mi serve per scorporare il parse dell'input dal tempo di esecuzione
 *
 * esegue prepara ( lettura numeri )
 * esegue programma completo ( lettura + algoritmo )
 * per poi far la differenza e scorporare solo il tempo effettivo di esecuzione dell'algoritmo 
 */
Tempi tempoMedioNetto(float tMin, char* batteria, int key, string exe){

    float ripTara, ripLord, t0, t1, tTara, tLordo, tMedio;

    // calcolo il numero di ripetizioni che mi servono rispetto alla granularità ( tMin )
    // calcolata per questo misurazione 
    ripTara = calcolaRipPrepara(  tMin , batteria, key, exe);
    ripLord = calcolaRip(tMin, batteria, key, exe);

    //cout << "calcolo tempo Tara" << endl;
    // eseguo il prepara rip volte per avere una buona stima 
    t0 = clock();
    for( int i = 1; i <= ripTara; i++){
        prepara( batteria );
    }
    t1 = clock();
    tTara = (t1-t0)/CLOCKS_PER_SEC;

    //cout << "calcolo tempo Lordo" << endl;
    // eseguo prepara + algo rip volte per avere una buona stima 
    t0 = clock();
    for( int i = 1; i <= ripLord; i++){
        prepara( batteria );
        launchExe( batteria, key , exe);
    }
    t1 = clock();

    // calcolo dei tempi 
    tLordo = (t1-t0)/CLOCKS_PER_SEC;
    tMedio = (tLordo/ripLord) - (tTara/ ripTara);

    Tempi t;
    t.tTot = tLordo;
    t.tMedio = tMedio;

    return t;
}


// dove tMin = granularità()/k
// c sono le misurazioni da fare
MisurazioniT misurazione(char* batteria , int dim, int key, int c, double za, float tMin, double delta, string exe ){

    vector<double> vec; 
    float sum2, cn, t;
    float m, e, s , myDelta;
    Tempi _t, __t;

    t = 0;
    sum2 = 0;
    cn = 0;
    //cout << "Sto misurando per la dimensione " << dim << endl; 
    do{
        for( int i = 1; i <= c; i++){

            // con preparazione input
            __t = tempoMedioNetto( tMin, batteria, key, exe);
            vec.push_back( __t.tMedio ); 
            m = __t.tMedio;

            t = t + m;
            sum2 =  sum2 + pow( m, 2);
        }
        cn += c;
        e = t/cn;

        s = sqrt( (sum2/cn) - pow(e, 2) );
        myDelta = (1/ sqrt(cn))*za*s;
   

    } while( myDelta >= delta );

    //cout << e; 
    MisurazioniT mis;
    mis.sd = standar_deviation( vec ); 
    mis.delta = myDelta;
    mis.e = e;
    cout << endl; 

    return mis;
}



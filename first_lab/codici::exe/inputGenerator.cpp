//
// Created by Riccardo Ferrarese on 07/11/2019.
//

#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "inputGenerator.h"

using namespace std;

float seed = 123456789;

float randomGenerator() {

    const int a = 16087;
    const int m = 2147483647;
    const int q = 127773;
    const int r = 2836;


    float lo, hi, test;

    hi = ceil(seed / q);
    lo = seed - q * hi;
    test = a * lo - r * hi;
    if (test < 0.0) {
        seed = test + m;
    } else {
        seed = test;
    }
    return seed / m;
}

// 99 campioni con lunghezza crescente e numeri random
// 5 campioni con lunghezza 100 e un solo numero random

void generateInFile() {

    seed = 123456789;

    // GENERAZIONE DEI FILE E DEI DATI CHE VERRANNO DATI IN PASTO ALL'ALGORITMO TRAMITE UNO SCRIPT .sh


    // CAMPIONI CON LUNGHEZZE PROGRESSIVE
    for (int i = 1; i < 100; i++) {

        stringstream ss;
        ss << "in-" << i;
        string name = ss.str();

        string path = "/Users/riccardo/Documents/ProgettoASD/test/" + name;
        ofstream myfile;
        myfile.open(path);

        for (int j = 0; j < i + 1; j++) {


            myfile << randomGenerator() * 1000 << " ";
            if (j < i) {
                myfile << ", ";
            }

        }
        myfile << ".";
        myfile.close();

    }

    /*
    int count = 100;
    //CAMPIONI CON DISTRIBUZIONE
    for( int i = 0; i < 5; i++){

        stringstream ss;
        ss << "in-" << count;
        string name = ss.str();

        string path="/Users/riccardo/Documents/ProgettoASD/test/"+name;
        ofstream myfile;

        myfile.open(  path );

        float my_random= randomGenerator()*100;

        for( int j = 0;j < 100; j++){


            myfile << my_random << " ";
            if( j < 99 ){
                myfile << ", ";
            }

        }
        myfile << "." ;
        myfile.close();
        count++;
    }*/

}

char *generateWithDim_Razionale(int dim) {

        // todo seed
        seed = seed * 2;

    int i;
    string str;
    stringstream ss;

    for (i = 0; i < dim; i++) {

       ///generazione del numero RAZIONALE POSITIVO 
        float d = randomGenerator()*10000;
        float n = randomGenerator()*1000;

        int num = static_cast<int>(n);
        int den = static_cast<int>(d);
        float my_rand = (float)num/den;

        ss << to_string(my_rand);

        if (i == dim - 1) {
            ss << '.';
        } else {
            ss << ' ';
            ss << ',';
        }


    }
    str = ss.str();

    // for convert string in char *
    char *writable = new char[str.size() + 1];
    copy(str.begin(), str.end(), writable);
    writable[str.size()] = '\0'; // don't forget the terminating 0

    return writable;
}


string generate_string(int dim) {

        // todo seed
    seed = seed * 2;

    int i;
    string str;
    stringstream ss;

    float n ;
    for (i = 0; i < dim; i++) {

        n = randomGenerator()*100;
        int num = static_cast<int>(n);

        ss << to_string(num);
        ss << ' ' ; 
    }

    str = ss.str();
    return str;
}

string generateEqualNum(int dim) {

        // todo seed
        seed = seed * 2;

    int i;
    string str;
    stringstream ss;

    float n = randomGenerator()*100;
    for (i = 0; i < dim; i++) {

        int num = static_cast<int>(n);

        ss << to_string(num);
        ss << ' ' ; 
    }

    str = ss.str();

    return str;
}

string generateMezzo( int dim ){

    seed = seed * 2;

    int i;
    string str;
    stringstream ss;

    float n = randomGenerator()*100;
    for (i = 0; i < dim/2; i++) {

        int num = static_cast<int>(n);

        ss << to_string(num);
        ss << ' ' ; 
    }


    for (i = dim/2; i < dim; i++) {
            float n1 = randomGenerator()*100;
        int num = static_cast<int>(n);

        ss << to_string(num);
        ss << ' ' ; 
    }

    str = ss.str();

    return str;
}


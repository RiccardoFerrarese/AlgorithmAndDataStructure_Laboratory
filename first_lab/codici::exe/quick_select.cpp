//
// Created by Riccardo Ferrarese on 11/01/2020.
//
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std; 

    int partition( vector<int> &vec, int start, int end);
    int quick_select_rec(vector<int> &vec, int start, int end, int k );
    int quick_select(vector<int> &vec, int k );

template <typename T>               // consumes a line of input stream and converts it into a vector
istream &operator >> (istream &in, vector<T> &vec) {
    string line;
    getline(in, line);              // read entire line from input stream
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

// int main(int argc, char** argv){

//     vector<int> vec; 
//     int key; int res; 

//     cin >> vec; 
//     cin >> key; 

//     res = quick_select( vec, key ); 

//     cout << res; 
//     return 0; 

// }

int exe( string in, int key){

    vector<int> vec; 
    int res; 

    istringstream s(in);          // create new stream from line
    
    int value;
    while (s >> value)              // turn line stream into vector
        vec.push_back(value);

    res = quick_select( vec, key ); 

    //cout << res; 
    return 0; 
}


/**
 * procedura per il calcolo del k-esimo elemento più piccolo dell'array
 *
 * @param vec -> array di interi positivi e negativi, non ordinato
 * @param dim
 * @param k
 * @return elemento in posizione k se l'array fosse ordinato
 */
int quick_select(std::vector<int> &vec, int k ){
    return quick_select_rec( vec, 0, vec.size()-1, k );
}


/**
 * Procedura ricorsiva
 * Utilizza partition per
 * @param vec
 * @param i -> indice inizio parte dell'array
 * @param j -> indice dell'ultimo elemento
 * @param k
 * @return
 */
int quick_select_rec(std::vector<int> &vec, int i, int j, int k) {

    // se k è compreso tra [i, j] eseguo
    // altrimenti termino la chiamata ricorsiva
    //cout <<"indici : " << i << "\t" << j << endl;

    if( k-1 >= i && k-1 <= j) {

            //cout << "ricorsione: "  << endl << "___partition" << endl;
            int pivot_index = partition( vec, i, j);
            //cout << "pivot per partition: " << pivot_index << endl;

            /// se l'indice del pivot corrisponde a (k-1) è l'elemento che cerco
            if (pivot_index == k - 1 ) 
                return vec[pivot_index];
            else if( pivot_index > k-1 )
                return quick_select_rec(vec, i, pivot_index - 1, k);
            
            return quick_select_rec(vec, pivot_index + 1, j, k);
    }

    return -1; 
}

/**
 * procedura per la partizione  dell'array in elementi
 * a sinistra più piccoli  del pivot ( non \leq
 * a destra numeri più grandi del pivot
 *
 * @param numbers
 * @param end --> indice dell'ultimo elemento
 * @return indice in cui si trova il pivot dopo il partizionamento
 */
int partition( vector<int> &vec, int start, int end){

    // utilizzo come pivot l'ultimo elemento dell'array
    int pivot = vec[end];
    int i = start-1;

    for (int j = start; j < end; j++){
        if (vec[j] <= pivot){                     // se l'emento preso è più piccolo o uguale del pivot incremeneto il primo
            i++;
            swap( vec[i], vec[j] ); 
        }
    }

    swap( vec[i+1], vec[end]); 

    return i+1;             //posizione pivot finale
}



//
// Created by Riccardo Ferrarese on 11/01/2020.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


void swap( int* a, int* b ){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

    int insertionsort(vector<int>& , int, int ); 
    int partition( vector<int>& , int , int , int );
    int findMedian(vector<int>& , int ); 
    int mOfm_select( vector<int>&, int, int, int ); 

int find_pivot( vector<int> &vec, int start, int end, int x ){

    int i; 
    for( i = start; i <= end; i++ ){
        if( vec[i] == x ){
            break; 
        }
    }
    return i; 
}

/**
 * procedura per la partizione  dell'array in elementi
 * attorno a x 
 * elementi <= x a sx 
 * elementi > x a dx 
 *
 * @param numbers
 * @param r --> indice dell'ultimo elemento
 * @return indice in cui si trova il pivot dopo il partizionamento
 */
int partition(vector<int> &arr, int l, int r, int x){ 
    
    int pos_pivot = find_pivot( arr, l, r, x); 

    swap( &arr[pos_pivot], &arr[r]); 

    int i = l-1; 
    for ( int j = l; j < r; j++ ) {
        if (arr[j] <= x) { 
            i++;
            swap( &arr[i], &arr[j]); 
        }
    } 
    swap( &arr[i+1], &arr[r]); 
    return i+1; 
} 

/**
 * Procedura per ordinare un'array di numeri 
 * per dimensione dell'array < 10 ha complessità lineare
 * @param end ___indice__ dell'ultimo elemento 
 * @return array ordinato
 */
vector<int> insertionSort(vector<int> &array, int start, int end) {
 
    for (int j = 0; j < array.size(); j++) {

        int key = array[j];
        int i = j - 1;
        while (i >= 0 && array[i] > key) {
            array[i + 1] = array[i];
            i = i - 1;
        }
        array[i + 1] = key;
    }
    return array;
}

/** Procedura per trovare l'elemento mediano 
 *  essendo n <= 5  ha ordinamento lineare 
 */
int findMedian(vector<int> &p_arr, int start, int end){

    // copio l'array per poi ordinarlo ( in modo da non toccare l'arr iniziale )
    int dim = end-start+1; 
    vector<int> my_arr ( dim ); 

    for( int i = 0; i < dim; i++ ){
        my_arr[i] = p_arr[start+i]; 
    } 

    vector<int> arr = insertionSort( my_arr, start, end ); 

    int med = arr[ arr.size()/2 ]; 
    arr.clear(); 

    return med;  // Return middle element 
}

int mOfm_select( vector<int> &arr, int left, int right, int k ){

    int dim = right-left+1;  // dimensio effettiva -> left = 0, right = 9 -> dim = 10 
    if( k > 0 && k <= dim ){    // k va da [1, dim ]

        // divido l'array in gruppetti di 5 e trovo i mediani 
        vector<int> median( (dim+4)/5 );
        int i; 
        for( i = 0; i < dim/5; i++ ){
            median[i] = findMedian( arr, left+i*5, left+i*5+4 ); 
        }

        // se avanzano elementi dai gurppetti di cinque 
        if( i*5 < dim ){
           median[i] =  findMedian( arr, left+i*5, right ); 
           i++; 
        }

        // ricorsivamente trovo il mediano dei medinai 
        int medOfMed; 
        if( i <= 5 ){
            medOfMed = findMedian( median, 0, i-1 ); 
        } else {
            medOfMed = mOfm_select( median, 0, i-1, i/2 ); 
        }

        int pos = partition( arr, left, right, medOfMed );

        if( pos-left == k-1 )
            return arr[pos]; 
        else if( pos-left > k-1 )
            return mOfm_select( arr, left, pos-1, k ); 

        return mOfm_select( arr, pos+1, right, k-pos+left-1); 
    } 
    return INT8_MAX; 
}

int exe_mOfm( string in, int key){

    vector<int> vec; 
    int res; 

    istringstream s(in);          // create new stream from line
    
    int value;
    while (s >> value)              // turn line stream into vector
        vec.push_back(value);

    res = mOfm_select( vec, 0, vec.size()-1, key ); 

    //cout << res; 
    return 0; 
}


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

int main( int argc, char** argv ){

    vector<int> vec; 
    int key; int res; 

    cin >> vec; 
    cin >> key; 
    
    cout << mOfm_select( vec, 0, vec.size()-1, key ); 
    return 0; 
}


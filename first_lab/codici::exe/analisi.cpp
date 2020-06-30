#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <vector>

// include file algoritmi 
#include "inputGenerator.cpp"

using namespace std;

    int partition( vector<int> &vec, int start, int end);
    int quick_select_rec(vector<int> &vec, int start, int end, int k );
    int quick_select(vector<int> &vec, int k );
    int insertionsort(vector<int>& , int, int ); 
    int partition( vector<int>& , int , int , int );
    int findMedian(vector<int>& , int ); 
    int mOfm_select( vector<int>&, int, int, int ); 

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

void _swap( int* a, int* b ){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}
// ___________________ codici algoritmi __________________ 


// Strutture dati per Min e Max heap 

// Strutture dati per heap ausiliare in cui gli elementi 
// sono indici dei valori contenuti nelle rispettive heap 
struct MaxHeap
{
public:

	vector<int> A;

	// return parent of A[i]
	int PARENT(int i) { 
        if( A.size() == 0 ){ return 0; }
		return (i - 1) / 2; 
	}

	// return left child of A[i]	
	int LEFT(int i) { 
		return (2 * i + 1); 
	}

	// return right child of A[i]	
	int RIGHT(int i) { 
		return (2 * i + 2); 
	}

	void heapify(int i){
		
		int left = LEFT(i);
		int right = RIGHT(i);

		int m = i;

		if (left < size() && A[left] > A[i])
			m = left;

		if (right < size() && A[right] >= A[m])
			m = right;

		if (m != i) {
			_swap( &A[i], &A[m]);
			heapify(m);
		}
	}

	int size(){
		return A.size();
	}

    void clear(){
        A.clear(); 
    }

    void heapify_up( int i ){
        int parent = (i - 1) / 2; 
  
        while( i > 0 && A[ PARENT(i) ] < A[i] ){
            _swap( &A[ PARENT(i)], &A[i] );
            i = PARENT(i); 
        }

    }
	

	void insert(int key, int dim ){
        
        A.resize( dim ); 
        // aggiungo elemento e chiamo heapify per garanti la proprietà della heap
		A.push_back(key);
		int i = A.size() - 1;
		heapify_up( i ); 
	}

	int extractMax(){
		
        int max; 
           if( size() == 1 ){
               max = A[0]; 
               A.pop_back(); 
               return max; 
           } 

           max = A[0]; 
           A[0] = A.back();
           A.pop_back(); 
           heapify( 0 ); 

        return max; 
	}

	int max(){
        if (size() == 0)
            cout << "index is out of range(Heap underflow)\n";
		return A.at(0);	// return A[0];
	}

    void buildHeap( vector<int> &vec){
        
        int dim = vec.size(); 
        A.resize( dim ); 
        for( int i = 0; i < dim; i++ ){
            A[i] = vec[i]; 
        }
        for( int i = A.size()/2 -1; i >= 0; i-- ){
            heapify( i ); 
        }
    }

    void print(){
        for( int i = 0; i < A.size(); i++ ){
            cout << A.at(i) << ' '; 
        }
        cout << endl; 
    }
};


struct MaxHeapAux{

    public: 
    
    // gli elementi di questo array sono degli indici che si riferisco 
    // alle posizioni degli elementi nella heap statica 
    vector<int> A; 

	int PARENT(int i) { 
        if( A.size() == 0 ){ return 0; }
		return (i - 1) / 2; 
	}

	// return left child of A[i]	
	int LEFT(int i) { 
		return (2 * i + 1); 
	}

	// return right child of A[i]	
	int RIGHT(int i) { 
		return (2 * i + 2); 
	}

    int size(){
        return A.size(); 
    }

    void heapify_up( int i , MaxHeap h ){

        int parent = (i - 1) / 2; 
        while( i > 0 && h.A[ A[PARENT(i)] ] < h.A[ A[i] ] ){
            _swap( &A[ PARENT(i)], &A[i] );
            i = PARENT(i); 
        }

    }
	
	void insert(int key_index, int dim , MaxHeap h){
        
        A.resize( dim ); 
     
		A.push_back( key_index );
		int i = A.size() - 1;
		heapify_up( i , h ); 
	}

    void heapify(int i, MaxHeap h){

		int left = LEFT(i);
		int right = RIGHT(i);

		int m = i;

        // faccio il confronto andando a vedere in h l'elemento alla posizione A[i] 
		if (left < size() && h.A[ A[left] ] > h.A[ A[i] ])
			m = left;

		if (right < size() && h.A[ A[right] ] > h.A[ A[m] ])
			m = right;

        //scambio degli indici ( i valori sono contenuti nella heap statica )
		if (m != i) {
			_swap( &A[i], &A[m]);
			heapify(m, h);
		}
	}

	// ritorno l'indice dell'elemento di h che in questa heap ausiliare è il minimo 
	int extractMin( MaxHeap h ){
		
        int max; 
           if( size() == 1 ){
               max =  A[0] ; 
               A.pop_back(); 
               return max; 
           } 

           max =  A[0] ; 
           A[0] = A.back();
           A.pop_back(); 
           heapify( 0, h ); 

        return max; 
	}

    void print(){
        for( int i = 0; i < A.size(); i++ ){
            cout << A.at(i) << ' '; 
        }
        cout << endl; 
    }

}; 


struct MinHeap
{
public:

	vector<int> A;

	// return parent of A[i]
	int PARENT(int i) { 
        if( A.size() == 0 ){ return 0; }
		return (i - 1) / 2; 
	}

	// return left child of A[i]	
	int LEFT(int i) { 
		return (2 * i + 1); 
	}

	// return right child of A[i]	
	int RIGHT(int i) { 
		return (2 * i + 2); 
	}

	void heapify(int i){

		int left = LEFT(i);
		int right = RIGHT(i);

		int m = i;

		if (left < size() && A[left] < A[i])
			m = left;

		if (right < size() && A[right] <= A[m])
			m = right;

		if (m != i) {
			_swap( &A[i], &A[m]);
			heapify(m);
		}
	}

	int size(){
		return A.size();
	}

    void clear(){
        A.clear(); 
    }

    void heapify_up( int i ){

        int parent = (i - 1) / 2; 
  
        while( i > 0 && A[ PARENT(i) ] > A[i] ){
            _swap( &A[ PARENT(i)], &A[i] );
            i = PARENT(i); 
        }

    }
	
	
	void insert(int key, int dim ){
        
        A.resize( dim ); 
        // aggiungo elemento e chiamo heapify per garanti la proprietà della heap
		A.push_back(key);
		int i = A.size() - 1;
		heapify_up( i ); 
	}

	int extractMin(){
		
        int min; 
           if( size() == 1 ){
               min = A[0]; 
               A.pop_back(); 
               return min; 
           } 

           min = A[0]; 
           A[0] = A.back();
           A.pop_back(); 
           heapify( 0 ); 

        return min; 
	}

	int min(){
        if (size() == 0)
            cout << "index is out of range(Heap underflow)\n";
		return A.at(0);	// return A[0];
	}

    void buildHeap( vector<int> &vec){
        
        int dim = vec.size(); 
        A.resize( dim ); 
        for( int i = 0; i < dim; i++ ){
            A[i] = vec[i]; 
        }
        for( int i = A.size()/2 -1; i >= 0; i-- ){
            heapify( i ); 
        }
    }

    void print(){
        for( int i = 0; i < A.size(); i++ ){
            cout << A.at(i) << ' '; 
        }
        cout << endl; 
    }
};


struct MinHeapAux{

    public: 
    
    // gli elementi di questo array sono degli indici che si riferisco 
    // alle posizioni degli elementi nella heap statica 
    vector<int> A; 

        // return parent of A[i]
	int PARENT(int i) { 
        if( A.size() == 0 ){ return 0; }
		return (i - 1) / 2; 
	}

	// return left child of A[i]	
	int LEFT(int i) { 
		return (2 * i + 1); 
	}

	// return right child of A[i]	
	int RIGHT(int i) { 
		return (2 * i + 2); 
	}

    int size(){
        return A.size(); 
    }

    void heapify_up( int i , MinHeap h ){

        int parent = (i - 1) / 2; 
        while( i > 0 && h.A[ A[PARENT(i)] ] > h.A[ A[i] ] ){
            _swap( &A[ PARENT(i)], &A[i] );
            i = PARENT(i); 
        }

    }

	void insert(int key_index, int dim , MinHeap h){
        
        A.resize( dim ); 
     
		A.push_back( key_index );
		int i = A.size() - 1;
		heapify_up( i , h ); 
	}

    void heapify(int i, MinHeap h){

		int left = LEFT(i);
		int right = RIGHT(i);

		int m = i;

        // faccio il confronto andando a vedere in h l'elemento alla posizione A[i] 
		if (left < size() && h.A[ A[left] ] < h.A[ A[i] ])
			m = left;

		if (right < size() && h.A[ A[right] ] <= h.A[ A[m] ])
			m = right;

        //scambio degli indici 
		if (m != i) {
			_swap( &A[i], &A[m]);
			heapify(m, h);
		}
	}

	// ritorno l'indice dell'elemento di h che in questa heap ausiliare è il minimo 
	int extractMin( MinHeap h ){
		
        int min; 
           if( size() == 1 ){
               min =  A[0] ; 
               A.pop_back(); 
               return min; 
           } 

           min =  A[0] ; 
           A[0] = A.back();
           A.pop_back(); 
           heapify( 0, h ); 

        return min; 
	}

    void print(){
        for( int i = 0; i < A.size(); i++ ){
            cout << A.at(i) << ' '; 
        }
        cout << endl; 
    }

}; 

// ____________________________________________________________ //

    int min_heap_select( vector<int>& vec, int k );
    int max_heap_select( vector<int>& vec,  int k );
    int heap_select( vector<int>& vec,  int k);

int max_heap_select( vector<int>& vec, int k ){

    MaxHeap h1;
    MaxHeapAux h2; 

    h1.buildHeap( vec ); 
    h2.insert( 0, 0, h1 ); 

    int i = 0; 
    int new_k = h1.size() - k +1;
    while( i < new_k-1 ){

        int x = h2.extractMin( h1 ); 

        int l_index = (2*x +1); 
        int r_index = (2*x + 2); 
        

        // inserisco gli indici del figlio destro e sinistro 
        int dim = h2.size()-1; 
        if( l_index < h1.size() ){
            dim++; 
            h2.insert( l_index, dim, h1); 
        }

        if( r_index < h1.size() ){
            dim++; 
            h2.insert( r_index, dim, h1 ); 
        }
        i++; 
    }
    return h1.A[ h2.extractMin( h1 ) ]; 
}

int min_heap_select( vector<int>& vec, int k ){

    MinHeap h1;
    MinHeapAux h2; 

    h1.buildHeap( vec ); 
    h2.insert( 0, 0, h1 ); 

    int i = 0; 
    while( i < k-1 ){

        int x = h2.extractMin( h1 ); 

        int l_index = (2*x +1); 
        int r_index = (2*x + 2); 
        

        // inserisco gli indici del figlio destro e sinistro 
        int dim = h2.size()-1; 
        if( l_index < h1.size() ){
            dim++; 
            h2.insert( l_index, dim, h1); 
        }

        if( r_index < h1.size() ){
            dim++; 
            h2.insert( r_index, dim, h1 ); 
        }
        i++; 
    }
    return h1.A[ h2.extractMin( h1 ) ]; 
} 


int heap_select( vector<int>& vec, int k ){

    if( k > vec.size()/2 ){
        return max_heap_select( vec, k ); 
    }  
    return min_heap_select( vec, k );
}


int exe_heap( string in, int key){

    vector<int> vec; 
    int res; 

    istringstream s(in);          // create new stream from line
    
    int value;
    while (s >> value)              // turn line stream into vector
        vec.push_back(value);

    res = heap_select( vec, key ); 

    //cout << res; 
    return 0; 
}

/// _________________________________________________________________________


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


/// _________________________________________________________________________

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

    _swap( &arr[pos_pivot], &arr[r]); 

    int i = l-1; 
    for ( int j = l; j < r; j++ ) {
        if (arr[j] <= x) { 
            i++;
            _swap( &arr[i], &arr[j]); 
        }
    } 
    _swap( &arr[i+1], &arr[r]); 
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

// ____________________ misurazione _____________________ 

float granularita(){

    float t0 = clock();
    float t1 = clock();

    while( t1 == t0){
        t1 = clock();
    }
    return (t1-t0)/CLOCKS_PER_SEC;
}


void parseInt(string in){
    vector<int> vec; 
    istringstream s(in);          // create new stream from line
    
    int value;
    while (s >> value)              // turn line stream into vector
        vec.push_back(value);
}

void prepara( string batteria ){
    parseInt(batteria);
}

float media( vector<float> vec){
    int dim = vec.size(); 
    float sum = 0.0, mean; 
    int i; 

    for(i = 0; i < dim; ++i)
        sum += vec[i];

    mean = sum/vec.size();
    return mean ;
}

float standar_deviation( vector<float> vec){

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

vector<float> misurazione_quick(string batteria, int dim, int key, int c, float tMin ){

    int rip, rip_prepara; 
    float t0, t1, t, tMedio, tMedio_prep, tEff; 
    vector<float> tempi; 

    // ripeto la misurazione con input diversi c volte 
    for( int k = 1; k <= c; k++ ){
        batteria = generate_string( dim );
        t0 = 0, t1 = 0;
        rip = 0;
        rip_prepara = 0; 

            // misuro tempo utilizzato per il parse dell'input 
            // inizio misurazione
            t0 = clock();
            while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
                    rip_prepara += 1; 
                    // eseguo sullo stesso input e key fino a superare tMin
                    prepara( batteria ); 
                    t1 = clock();
            }
            t = (t1-t0)/CLOCKS_PER_SEC; 
            tMedio_prep = t/rip_prepara; 

    // misuro tempo in un ciclo while fino a superare tMin
    // per avere il tempo medio divido per il numero di iterazioni fatte 
        t0 = 0; t1 = 0; 
            // inizio misurazione
            t0 = clock();
            while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
                    rip += 1; 
                    // eseguo sullo stesso input e key fino a superare tMin
                    exe( batteria, key ); 
                    //exe_heap( batteria, key ); 
                    //exe_mOfm( batteria, key ); 
                    t1 = clock();
            }
            t = (t1-t0)/CLOCKS_PER_SEC; 
            tMedio = t/rip;
            //cout << tMedio << ' ' ; 

        //cout << endl; 
        // calcolo tempo effettivo senza lettura input 
        tEff = tMedio - tMedio_prep;
        tempi.push_back( tEff ); 
    }
    return tempi; 
}


vector<float> misurazione_heap(string batteria, int dim, int key, int c, float tMin ){

    int rip, rip_prepara; 
    float t0, t1, t, tMedio, tMedio_prep, tEff; 
    vector<float> tempi; 

    // ripeto la misurazione con input diversi c volte 
    for( int k = 1; k <= c; k++ ){
        batteria = generate_string( dim );
        t0 = 0, t1 = 0;
        rip = 0;
        rip_prepara = 0; 

            // misuro tempo utilizzato per il parse dell'input 
            // inizio misurazione
            t0 = clock();
            while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
                    rip_prepara += 1; 
                    // eseguo sullo stesso input e key fino a superare tMin
                    prepara( batteria ); 
                    t1 = clock();
            }
            t = (t1-t0)/CLOCKS_PER_SEC; 
            tMedio_prep = t/rip_prepara; 

    // misuro tempo in un ciclo while fino a superare tMin
    // per avere il tempo medio divido per il numero di iterazioni fatte 
        t0 = 0; t1 = 0; 
            // inizio misurazione
            t0 = clock();
            while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
                    rip += 1; 
                    // eseguo sullo stesso input e key fino a superare tMin
                    //exe( batteria, key ); 
                    exe_heap( batteria, key ); 
                    //exe_mOfm( batteria, key ); 
                    t1 = clock();
            }
            t = (t1-t0)/CLOCKS_PER_SEC; 
            tMedio = t/rip;
            //cout << tMedio << ' ' ; 

        //cout << endl; 
        // calcolo tempo effettivo senza lettura input 
        tEff = tMedio - tMedio_prep;
        tempi.push_back( tEff ); 
    }
    return tempi; 
}


vector<float> misurazione_mOfm(string batteria, int dim, int key, int c, float tMin ){

    int rip, rip_prepara; 
    float t0, t1, t, tMedio, tMedio_prep, tEff; 
    vector<float> tempi; 

    // ripeto la misurazione con input diversi c volte 
    // ne vado a calcolare media e standard deviation
    for( int k = 1; k <= c; k++ ){
        batteria = generate_string( dim );
        t0 = 0, t1 = 0;
        rip = 0;
        rip_prepara = 0; 

            // misuro tempo utilizzato per il parse dell'input 
            // inizio misurazione
            t0 = clock();
            while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
                    rip_prepara += 1; 
                    // eseguo sullo stesso input e key fino a superare tMin
                    prepara( batteria ); 
                    t1 = clock();
            }
            t = (t1-t0)/CLOCKS_PER_SEC; 
            tMedio_prep = t/rip_prepara; 

    // misuro tempo in un ciclo while fino a superare tMin
    // per avere il tempo medio divido per il numero di iterazioni fatte 
        t0 = 0; t1 = 0; 
            // inizio misurazione
            t0 = clock();
            while( (t1-t0)/CLOCKS_PER_SEC <= tMin){
                    rip += 1; 
                    // eseguo sullo stesso input e key fino a superare tMin
                    //exe( batteria, key ); 
                    //exe_heap( batteria, key ); 
                    exe_mOfm( batteria, key ); 
                    t1 = clock();
            }
            t = (t1-t0)/CLOCKS_PER_SEC; 
            tMedio = t/rip;
            //cout << tMedio << ' ' ; 

        //cout << endl; 
        // calcolo tempo effettivo senza lettura input 
        tEff = tMedio - tMedio_prep;
        tempi.push_back( tEff ); 
    }
    return tempi; 
}

void analisi_tempi(){

    const double k = 0.01;
    const double za = 3.27;
    float tMin;
    int c = 50;
    int campioni = 1000; 
    string batteria; int key; 
    float temp; float sd_temp; 

    vector<float> tempi; 

    /// per scrittura risultati su file 
    //string path="/Users/riccardo/Desktop/ASD_vs/Grafici_tot/tempi.csv";
    //ofstream myfile;
    //myfile.open( path );   
    /////
    //myfile << "Dim,Key,TempoM"<<endl; 

    int dim; 

    // calcolo tMin
    tMin = granularita()/k; 
    cout << tMin << endl;

    for( int i = 1000; i <= 10000; i = i + 10 ){
        dim = i; 
        // GENERO BATTERIA E KEY 
        batteria = generate_string( dim );         // worst case con num tutti uguali
        key = 100; 

        // reset parametri
        tempi = misurazione_quick(batteria, dim, key, c, tMin );  
        temp = media( tempi );
        sd_temp = standar_deviation( tempi ); 

        cout << dim << ' ' << key << ' ' << temp << ' ' << sd_temp << ' '; 

        tempi = misurazione_heap(batteria, dim, key, c, tMin );  
        temp = media( tempi );
        sd_temp = standar_deviation( tempi ); 

        cout << temp << ' ' << sd_temp << ' '; 

        tempi = misurazione_mOfm(batteria, dim, key, c, tMin );  
        temp = media( tempi );
        sd_temp = standar_deviation( tempi ); 

        cout << temp << ' ' << sd_temp << ' ' << endl; 
        //myfile << dim << ',' << key << ',' << temp <<  ',' << sd_temp << endl; 
    }
    //myfile.close(); 
}
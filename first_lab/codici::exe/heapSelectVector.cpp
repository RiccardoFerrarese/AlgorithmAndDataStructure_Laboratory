//
// Created by Riccardo Ferrarese on 18/03/2020.
//

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std; 


void swap( int* a, int* b ){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

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
			swap( &A[i], &A[m]);
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
            swap( &A[ PARENT(i)], &A[i] );
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
            swap( &A[ PARENT(i)], &A[i] );
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
			swap( &A[i], &A[m]);
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
			swap( &A[i], &A[m]);
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
            swap( &A[ PARENT(i)], &A[i] );
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
            swap( &A[ PARENT(i)], &A[i] );
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
			swap( &A[i], &A[m]);
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

int main(int argc, char** argv ){

    vector<int> vec; 
    int key; int res; 

    cin >> vec; 
    cin >> key; 

    res =  heap_select( vec, key ); 

    cout << res; 
    return 0; 

}
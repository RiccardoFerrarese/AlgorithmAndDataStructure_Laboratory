#include <random>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>    // std::shuffle


#define RED 0
#define BLACK 1


using namespace std;

template <typename T>               // concerts a vector into a line of output stream
ostream &operator << (ostream &out, const vector<T> &vec) {
    for (int i = 0; i < vec.size(); i++)
        out << vec[i] << " ";

    out << endl;
    return out;
}

// ___________ ALGORITMI _______________________ 
/// __________________ BST _______________________ 

struct nodo{
    int key;
    string value;
    struct nodo *left;
    struct nodo *right;
}typedef  NODO ;

// tree -> puntatore a nodo
typedef struct nodo* tree;

void print_preorder(tree node){

    if (node == NULL)
        std::cout << "NULL ";
    else {
        std::cout << node->key << ":" << node->value << ' ' ;
        print_preorder(node->left);
        print_preorder(node->right);
    }
}

tree new_node( int key, string value ){

    tree node = new NODO;
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

bool Is_Empty(tree root){
    return (root==NULL);
}

// ricerca di una chiave nell'albero, ritorno il valore contenuto nel nodo con chiave key
// si assume che tale key esista
int tree_search( tree &root, int key ){

    tree x; 
    x = root;
    while(x != NULL && x->key != key){
		if(key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
    return x->key; 
}

bool find( tree root, int key ){

    if( root == NULL ){
        return false; 
    }
    tree x; 
    x = root; 
    while( x->key != key ){
        
            if( key < x->key ){
                if( x->left == NULL )
                    return false; 
                else 
                    x = x->left; 
            } else {
                if( x->right == NULL )
                    return false; 
                else 
                    x = x->right;
            }
    }
    return true; 
}

tree tree_insert( tree root, int key, string value ){

    tree new_node = new NODO;
    new_node->value = value;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    tree x = root;
    tree y = NULL;

    while( x != NULL ){ // scendo nell'albero
        y = x;
        if( key < x->key ){
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // root è null -> y nuova root
    if( y == NULL ){
        y = new_node;

    } else if( key < y->key ){ //posiziono il nuovo nodo
        y->left = new_node;
    } else {
        y->right = new_node;
    }

    return y;
}

//////////////////////////////////

void destroy_bst(tree node){  
    if (node == NULL) return;  
  
    // first delete subtrees
    destroy_bst(node->left);  
    destroy_bst(node->right);  
  
    delete node; 
}  

// ___________________________ AVL __________________________ 

struct nodo_avl{
    int key;
    string value;
    struct nodo_avl *left;
    struct nodo_avl *right;
    int height;
}typedef  NODO_AVL ;

// tree -> puntatore a nodo
typedef struct nodo_avl* tree_avl;

void print_preorder(tree_avl node){

    if (node == NULL)
        std::cout << "NULL ";
    else {
        std::cout << node->key << ":" << node->value << ':' << node->height << ' ' ;
        print_preorder(node->left);
        print_preorder(node->right);
    }
}

bool Is_Empty(tree_avl root){
    return (root==NULL);
}

// ritorna il sotto albero sinistro
tree_avl subTree_sx(tree_avl root){
    if (Is_Empty(root)) return(NULL);
    else return(root->left);
}

// ritorna il sotto albero destro
tree_avl subTree_dx(tree_avl root){
    if (Is_Empty(root)) return(NULL);
    else return(root->right);
}

// fuzione per ritornare l'altezza di un nodo
int height( tree_avl node ){
    if( node == NULL ){
        return 0;
    }
    return node->height;
}

int max(int a, int b){
    return (a > b)? a : b;
}

// ricerca di una chiave nell'albero, ritorno il valore contenuto nel nodo con chiave key
// si assume che tale key esista
int avl_tree_search( tree_avl root, int key ){
    tree_avl x; 
    x = root;
    while(x != NULL && x->key != key){
		if(key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

    return x->key;
}

tree_avl right_rotate(tree_avl y){
    tree_avl x = y->left;
    tree_avl T2 = x->right;  //sottoalbero di dx di y

    // Rotazione
    x->right = y;
    y->left = T2;

    // Aggiorno le altezze
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    
    return x;
}

tree_avl left_rotate(tree_avl x){
    tree_avl y = x->right;
    tree_avl T2 = y->left;  //sottoalbero di sx di x

    // Rotazione
    y->left = x;
    x->right = T2;

    // Aggiorno le altezze
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

int get_balance( tree_avl node ){
    if( node == NULL ){
        return 0;
    }
    return height( node->left ) - height( node->right );
}

tree_avl avl_tree_insert(tree_avl node, int key, string value) {

    // definisco il nuovo nodo e alloco memoria
    tree_avl new_node = new NODO_AVL;
    new_node->value = value;
    new_node->key = key;
    new_node->height = 1;       // aggiunti come foglia
    new_node->left = NULL;
    new_node->right = NULL;


    if (node == NULL)  // r è la root
        return node = new_node;

    if (key < node->key) {
        node->left = avl_tree_insert(node->left, key, value);
    } else if (key >= node->key) {
        node->right = avl_tree_insert(node->right, key, value);
    }

    // AGGIORNO ALTEZZA DEL PADRE
    node->height = 1 + max( height(node->left),
                            height(node->right));

    int balance = get_balance( node );
    // Se il nodo diventa non bilanciato
    // Left Left Case
    if ( balance > 1 && key < node->left->key )
        return right_rotate(node);

    // Right Right Case
    if ( balance < -1 && key > node->right->key )
        return left_rotate(node);

    // Left Right Case
    if ( balance > 1 && key > node->left->key ){
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left Case
    if ( balance < -1 && key < node->right->key ){
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

bool find( tree_avl root, int key ){

    if( root == NULL ){
        return false; 
    }
    tree_avl x; 
    x = root; 
    while( x->key != key ){
        
            if( key < x->key ){
                if( x->left == NULL )
                    return false; 
                else 
                    x = x->left; 
            } else {
                if( x->right == NULL )
                    return false; 
                else 
                    x = x->right;
            }
    }
    return true; 
}

void destroy_avl(tree_avl node){  
    if (node == NULL) return;  
  
    // first delete subtrees
    destroy_avl(node->left);  
    destroy_avl(node->right);  
  
    delete node; 
}  


///_____________________ RB _____________________________ 


/// RB
struct Nodo{
    int key;
    string value;
    int color;  /// int per risparmiare spazio -> RED 0 BLACK 1 
    struct Nodo *parent;
    struct Nodo *left;
    struct Nodo *right;

    Nodo( int key, string value ){
        this->key = key;
        this->value = value;
        left = right = parent = NULL;
        this->color = RED;
    }
};
// tree -> puntatore a nodo
typedef struct Nodo* tree_rb;

class RBTree
{
protected:
    void left_rotate(tree_rb &, tree_rb &);
    void right_rotate(tree_rb &, tree_rb &);
    void rb_insert_fixUp(tree_rb &, tree_rb &);
public:
    // Constructor
    tree_rb root;
    RBTree() { root = NULL; }
    void rb_tree_insert(int key,string value );
    string rb_tree_search(tree_rb &, int );
    bool find( tree_rb &, int);
    void print_preorder(tree_rb );
    void destroy(tree_rb node);
};

void RBTree::print_preorder(tree_rb node){

    if (node == NULL)
        std::cout << "NULL ";
    else {
        std::cout << node->key << ":" << node->value << ":";
        string color = (node->color == BLACK )? "black" : "red"; 
        std::cout << color << ' '; 
        print_preorder(node->left);
        print_preorder(node->right);
    }
}

tree_rb tree_insert( tree_rb root, tree_rb new_node ){

    tree_rb x = root;
    tree_rb y = NULL;

    while( x != NULL ){ // scendo nell'albero
        y = x;
        if( new_node->key < x->key ){
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // root è null -> y nuova root
    if( y == NULL ){
        return new_node;
    } else if( new_node->key < y->key ){ //posiziono il nuovo nodo
        y->left = new_node;
    } else {
        y->right = new_node;
    }
    new_node->parent = y;
    return root;
}
// ricerca di una chiave nell'albero, ritorno il valore contenuto nel nodo con chiave key
// si assume che tale key esista
string RBTree::rb_tree_search(tree_rb &root,  int key ){

    tree_rb x; 
    x = root;
    while(x != NULL && x->key != key){
		if(key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	return x->value;
}

void RBTree::left_rotate(tree_rb &root, tree_rb &x ){

    tree_rb y; 
    y = x->right; 
    x->right = y->left; 

    if( x->right != NULL )
        x->right->parent = x;

    y->parent = x->parent; 

    if( x->parent == NULL )
        root = y;
    else if( x == x->parent->left )
        x->parent->left = y; 
    else
        x->parent->right = y;         

    y->left = x; 
    x->parent = y; 
}

void RBTree::right_rotate(tree_rb &root, tree_rb &x){

    tree_rb y; 
    y = x->left; 
    x->left = y->right; 

    if( x->left != NULL )
        x->left->parent = x;

    y->parent = x->parent; 

    if( x->parent == NULL )
        root = y;
    else if( x == x->parent->left )
        x->parent->left = y; 
    else
        x->parent->right = y;         

    y->right = x; 
    x->parent = y;  
}

void RBTree::rb_insert_fixUp(tree_rb &root, tree_rb &x ){
    // per semplicità di lettura del codice definiamo:

    tree_rb padre_x = NULL;
    tree_rb nonno_x = NULL;
    while( x != root && x->color != BLACK && x->parent->color == RED  ){
        
        padre_x = x->parent;
        nonno_x = x->parent->parent;

        if( padre_x == nonno_x->left ){

                tree_rb zio_x = nonno_x->right; 
                /// caso 1 -- lo zio di x è rosso
                if( zio_x != NULL && zio_x->color == RED){
                    padre_x->color = BLACK;  // coloro il padre di x
                    zio_x->color = BLACK;             // coloro lo zio
                    nonno_x->color = RED;   // coloro il nonno
                    x = nonno_x; 
                            // il nonno di x diventa il nuovo x
            } else {
                /// caso 2 -- lo zio y di x è nero e x dallo stesso lato dello zio
                if( x == padre_x->right ){
                    left_rotate(root, padre_x );              // padre di x diventa il nuovo x e ..
                    x = padre_x;
                    padre_x = x->parent;
                }
                /// caso 3 -- lo zio y di x è nero e x è dal opposto dello zio
                right_rotate(root, nonno_x );
                swap( padre_x->color, nonno_x->color );
                x = padre_x;
            }
        } else { // caso simmetrico

            tree_rb zio_x = nonno_x->left;
            if( zio_x != NULL && zio_x->color == RED){
                padre_x->color = BLACK;
                zio_x->color = BLACK;
                nonno_x->color = RED;
                x = nonno_x;
            } else {
                if( x == padre_x->left ){
                    right_rotate(root, padre_x );
                    x = padre_x;
                    padre_x = x->parent;
                }
                left_rotate(root, nonno_x );
                swap( padre_x->color, nonno_x->color );
                x = padre_x;

            }
        }
    }
    root->color = BLACK;
}

void RBTree::rb_tree_insert(int key, string value  ){

    tree_rb new_node = new Nodo(key, value);
    root = tree_insert( root, new_node );
    rb_insert_fixUp(root, new_node );
}

bool RBTree::find( tree_rb &root, int key ){

    if( root == NULL ){
        return false; 
    }
    tree_rb x; 
    x = root; 
    while( x->key != key ){
        
            if( key < x->key ){
                if( x->left == NULL )
                    return false; 
                else 
                    x = x->left; 
            } else {
                if( x->right == NULL )
                    return false; 
                else 
                    x = x->right;
            }
    }
    return true; 
}

void RBTree::destroy(tree_rb node){  
    if (node == NULL) return;  
  
    // first delete subtrees
    destroy(node->left);  
    destroy(node->right);  
  
    delete node; 
}  


// ____________ misurazioni ________________ 
// _____ TUTTE LE MISURE SONO IN SECONDI ____ 

using namespace std::chrono; 

float seed = 123456789;

// calcolo della risoluzione del clock 
double granularita(){

    steady_clock::time_point t0 = steady_clock::now();
    steady_clock::time_point t1 = steady_clock::now();

    while( t1 == t0 ){
        t1 = steady_clock::now();
    }

    duration<double> time_span = duration_cast<duration<double> >(t1 - t0);
    double nseconds = time_span.count();
    return nseconds; 
}


double standar_deviation( vector<double> &vec){

    int dim = vec.size(); 
    double sum = 0.0, mean, variance = 0.0, stdDeviation;

    int i;
    for(i = 0; i < dim; ++i)
        sum += vec[i];

    mean = sum/vec.size();

    for(i = 0; i < dim; ++i)
        variance += pow(vec[i] - mean, 2);

    variance=variance/5;
    return stdDeviation = sqrt(variance);
}

double media_t( vector<double> &vec ){

    double sum;
    double media; 
    int dim = vec.size(); 
    for( int i = 0; i < dim; i++ ){
        sum += vec[i]; 
    }
    media = sum/ dim; 
    return media; 
}


double mis_bst(double tMin, int i, int keys[] ){

    steady_clock::time_point t0, t1; 
    duration<double> time_span = steady_clock::duration::zero(); 
    double nseconds = -1; 
    double t_medio, t_amm; 
    int n, m; 
    int k;

    tree tree; 
    //n = i; // ricerche
    //m = 0; // insert 

    t0 = steady_clock::now(); 
    int rip = 0; 
    // misuro rip volte fino a che non garantisco l'errore relativo massimo
    // esegue sempre un solo ciclo 
    while( nseconds < tMin ){
        //std::cout << "inizio misurazione.." << endl; 
        tree = NULL;
        n = i;  // ricerche da fare 
        while( n >= 0 ){ // per le N operazioni eseguo find e eventuale insert

                k = keys[n]; 
                bool res = find( tree, k ); 
                if( !res ){     // essendo spazio key grande, eseguo quasi sempre insert 
                    tree = tree_insert( tree, k, to_string(k) );
                   // m += 1; 
                }
            n--; 
        }
        //std::cout << "Ho misurato albero " << rip << endl; 
        t1 = steady_clock::now(); 
        time_span = (t1 - t0);
        //nseconds = double(time_span.count()) * steady_clock::period::num / steady_clock::period::den;
        nseconds = time_span.count(); 
        rip++; 
        destroy_bst( tree ); 
    }

    t_medio= nseconds/rip; 
    t_amm = t_medio/(i*2); // tempo totale / ( ricerca + inserimento )
    return t_amm; 
}

double mis_avl( double tMin, int i, int keys[] ){

    steady_clock::time_point t0, t1; 
    duration<double> time_span =  steady_clock::duration::zero(); 
    double nseconds = -1; 
    double t_medio, t_amm; 
    int n, m; 
    int k;
    tree_avl tree_avl; 
    //n = i; // ricerche
    //m = 0; // insert 

    t0 = steady_clock::now(); 
    int rip = 0; 
    while( nseconds < tMin ){
        tree_avl = NULL;
        n = i;  // ricerche da fare 
        while( n >= 0 ){

                k = keys[n];  
                bool res = find( tree_avl, k );         
                if( !res ){
                    tree_avl = avl_tree_insert( tree_avl, k, to_string(k) );
                    //m += 1; 
                }
            n--; 
        }
        t1 = steady_clock::now(); 
        time_span = (t1 - t0);
        //nseconds = double(time_span.count()) * steady_clock::period::num / steady_clock::period::den;
        nseconds = time_span.count(); 
        rip++; 
        destroy_avl( tree_avl ); 
    }

    t_medio= nseconds/rip; 
    t_amm = t_medio/(i*2); // tempo totale / ( ricerca + inserimento )
    return t_amm; 
}

double mis_rb( double tMin, int i, int keys[] ){

    steady_clock::time_point t0, t1; 
    duration<double> time_span =  steady_clock::duration::zero(); 
    double nseconds = -1; 
    double t_medio, t_amm; 
    int n, m; 
    int k;

    //n = i; // ricerche
    //m = 0; // insert 

    RBTree tree_rb; 
    t0 = steady_clock::now(); 
    int rip = 0; 
    while( nseconds < tMin ){
        n = i;  // ricerche da fare 
        while( n >= 0 ){
            k = keys[n];
            bool res = tree_rb.find(tree_rb.root, k );     
            if( res == false ){
                tree_rb.rb_tree_insert( k, to_string(k) );
                //m += 1; 
            }
            n--; 
        }

        t1 = steady_clock::now(); 
        time_span = (t1 - t0);
        //nseconds = double(time_span.count()) * steady_clock::period::num / steady_clock::period::den;
        nseconds = time_span.count(); 
        rip++; 
        tree_rb.destroy( tree_rb.root ); 
    } 

    t_medio= nseconds/rip; 
    t_amm = t_medio/(i*2); // tempo totale / ( ricerca + inserimento )
    return t_amm; 
}


void analisi_tree(){

    double media_bst, media_avl, media_rb, sd_bst, sd_avl, sd_rb, temp;
    int n, i, a, num; 
    float b; 
    double tMin, g; 

    vector<double> tempi_bst;
    vector<double> tempi_avl;
    vector<double> tempi_rb; 
    vector<int> keys; 

    std::cout << "Op Tempo_bst Sd_bst Tempo_avl Sd_avl Tempo_rb Sd_rb" << endl; 

    // calcolo tMin
    g = granularita(); 
    tMin = g/(g+0.01); // dove 0.01 errore relativo massimo ammesso

    srand ( seed );

    // mt19937 eng;  // a core engine class --> Mersenne Twister
    // geometric_distribution<int> geometric; 

     
    // N operazioni secondo distribuzione a*pow( b, i )
    a = 1000; 
    b = 1.0471;
    for( i = 0; i <= 101; i++ ){
        
        int dim =  a * pow( b, i ) ; 
        int* keys = (int*)malloc(sizeof(int)*dim);
    

        //geometric_distribution<int> geometric( (float)1/dim ); 
        
        for( int x = 0; x < 100; x++ ){ 
        
            
            // salvo le chiavi per la riesecuzione in caso non superasse tMin 
            for( int t = 0; t < dim; t++ ){
                
                num = rand()%1000000;
            
                keys[t] = num; 
                //keys.push_back( num ); // 0 <= num <= 99_999
                //keys.push_back( geometric(eng) ); 
            }

            //geometric.reset();  // indipendenza tra i vari pescaggi delle key

            temp =  mis_bst( tMin, dim, keys); 
            tempi_bst.push_back( temp ); 

            temp =  mis_avl( tMin, dim, keys );
            tempi_avl.push_back( temp ); 

            temp = mis_rb( tMin, dim, keys  ); 
            tempi_rb.push_back( temp ); 
        }

        free( keys ); 

        std::cout << endl; 
        media_bst = media_t( tempi_bst ); 
        media_avl = media_t( tempi_avl ); 
        media_rb = media_t( tempi_rb ); 

        sd_bst = standar_deviation( tempi_bst ); 
        sd_avl = standar_deviation( tempi_avl ); 
        sd_rb = standar_deviation( tempi_rb ); 

        tempi_bst.clear(); 
        tempi_avl.clear(); 
        tempi_rb.clear(); 

        std::cout << dim << ' ' << media_bst << ' ' << sd_bst << ' ' << media_avl << ' ' << sd_avl << ' ' << media_rb << ' ' << sd_rb; 
    }

}
//
// Created by Riccardo Ferrarese on 29/04/2020.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>

#define RED 0
#define BLACK 1

using namespace std;

template <typename T>               // consumes a line of input stream and converts it into a vector
istream &operator >> (istream &in, vector<T> &vec) {
    string line;
    getline(in, line);              // read entire line from input stream
    istringstream s(line);          // create new stream from line

    string value;
    while (s >> value)              // turn line stream into vector
        vec.push_back(value);
    return in;
}

//template <typename T>               // concerts a vector into a line of output stream
ostream &operator << (ostream &out, const vector<string> &vec) {
    for (int i = 0; i < vec.size(); i++)
        out << vec[i] << " ";
    out << endl;
    return out;
}

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
        cout << "NULL ";
    else {
        cout << node->key << ":" << node->value << ":";
        string color = (node->color == BLACK )? "black" : "red"; 
        cout << color << ' '; 
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

//////////////////////////////////

int main(){

    /**
     * finchè string in input non è "exit"
     * leggi prima word per confronto comando
     *      se è insert:
     *           leggi key
     *           leggi value
     *        output = ' '
     *
     *      se è find:
     *           leggi key
     *        output = $value
     */

    string line;
    string cmd;
    int key;
    string value;
    string result;

    RBTree tree;

    vector<string> in;
    cin >> in;
    cmd = in[0];

    while ( true ){
        if( cmd == "exit" ) {
            break;
        } else if( cmd == "insert" ) {

            key = stoi( in[1] );
            value = in[2];
            tree.rb_tree_insert( key, value);

        } else if( cmd == "find" ){

            key = stoi( in[1] );
            result = tree.rb_tree_search( tree.root, key );
            cout << result << endl;

        } else if( cmd == "show" ){
            tree.print_preorder( tree.root );
            cout << endl; 
        } else {
            cout << "Command error !!! " << endl;
        }

        in.clear();
        value = "NULL ";
        cin >> in;
        cmd = in[0];
    }

    return 0;
}


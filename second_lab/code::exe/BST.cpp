
#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>


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

/// BST


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
        cout << "NULL ";
    else {
        cout << node->key << ":" << node->value << ' ' ;
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
string tree_search( tree &root, int key ){

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
    return x->value; 
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

int main(int argc, char** argv) {

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

    tree tree = NULL ;

    vector<string> in;
    cin >> in;
    cmd = in[0];

    while ( true ){

        if( cmd == "exit" ) {
            break;
        } else if( cmd == "insert" ) {

            key = stoi( in[1] );
            value = in[2];
            if( tree == NULL ) {
                tree = tree_insert(tree, key, value);
            } else {
                tree_insert( tree, key, value );
            }

        } else if( cmd == "find" ){

            key = stoi( in[1] );
            result = tree_search( tree, key );
            cout << result << endl;

        } else if( cmd == "show" ){
            print_preorder( tree );
        } else {
            cout << "Command error !!! " << endl;
        }

        in.clear();
        value = "Null";
        cin >> in;
        cmd = in[0];
    }

    return 0;
}
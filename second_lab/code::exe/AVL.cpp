//
// Created by Riccardo Ferrarese on 29/04/2020.
//

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

/// AVL

/**
 * AVL nel nodo contiene informazioni dell'altezza
 */
struct nodo_avl{
    int key;
    string value;
    struct nodo_avl *left;
    struct nodo_avl *right;
    int height;
}typedef  NODO ;

// tree -> puntatore a nodo
typedef struct nodo_avl* tree_avl;

void print_preorder(tree_avl node){

    if (node == NULL)
        cout << "NULL ";
    else {
        cout << node->key << ":" << node->value << ':' << node->height << ' ' ;
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
string avl_tree_search( tree_avl root, int key ){
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

    return x->value;
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
    tree_avl new_node = new NODO;
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

    tree_avl tree_avl = NULL;

    vector<string> in;
    cin >> in;
    cmd = in[0];

    while ( true ){
        if( cmd == "exit" ) {
            break;
        } else if( cmd == "insert" ) {

            key = stoi( in[1] );
            value = in[2];
            tree_avl = avl_tree_insert( tree_avl, key, value );
            print_preorder( tree_avl );
            cout << endl;

        } else if( cmd == "find" ){

            key = stoi( in[1] );
            result = avl_tree_search( tree_avl, key );
            cout << result << endl;

        } else if( cmd == "show" ){
            print_preorder( tree_avl );
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

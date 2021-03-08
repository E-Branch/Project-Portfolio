#pragma once
#include <vector>
#include <iostream>
#include <cmath>
using std::vector;
using std::cout;
using std::endl;
using std::pow;

template <class K, class V>
class NodeT{
public:
	K key;
	V value;

	NodeT<K,V>* left;
	NodeT<K,V>* right;
	NodeT<K,V>* parent;

	bool isBlack;	
	
	NodeT(K key, V val): key(key), value(val), left(NULL), right(NULL),
		parent(NULL), isBlack(false) {};
	NodeT(NodeT<K,V>* copy_nd): key(copy_nd->key), value(copy_nd->value), isBlack(copy_nd->isBlack),
		left(NULL), right(NULL), parent(NULL) {};
};

template <class K, class V>
class RedBlackTree{
	
public:
	
	//constructors
	RedBlackTree();
	RedBlackTree( const RedBlackTree<K,V>& cpy_tree);
	
	//operator
	RedBlackTree<K,V>& operator=( const RedBlackTree<K,V>& cpy_tree);
	
	//destructor
	~RedBlackTree();
	
	//setters
	bool insert(K key, V val);
	bool remove(K key);
	
	//getters
	bool search(K key) const;
	vector<V> search(K key_start, K key_end) const;
	vector<V> values() const;
	vector<K> keys() const;
	int size() const;
	
	NodeT<K,V>* getRoot() const;
	
	
	//testing functions
	
	//level-order print of tree, recursive, red nodes have '*' next to them
	//this was annoying to do, because i had to look it up, but im so annoyed at not
	//being able to see the tree clearly
	void print_levels() const;
	
	void print_in_order() const;
	
//private:
	
	//PRIVATE MEMBERS
	//===============
	
	NodeT<K,V>* root;
	int current_size;
	
	// HELPER FUNCTIONS
	// ================
	
	//copyies the subtrees of copy_nd into current_nd
	void copy_subtree(NodeT<K,V>* current_nd, const NodeT<K,V>* copy_nd);
	
	//inserts a node into a tree and returns it
	NodeT<K,V>* BST_insert(K key, V val);
	void left_rotate(NodeT<K,V>* nd);
	void right_rotate(NodeT<K,V>* nd);
	void RedBlack_fix(NodeT<K,V>* fix_nd, NodeT<K,V>* parent_nd, bool is_left);
	
	//deallocates an entire subtree
	void remove_subtree(NodeT<K,V>* subtree);
	
	//removes the current node
	void remove(NodeT<K,V>* nd);
	
	//finds the predecessor of nd and returns it
	NodeT<K,V>* predecessor(NodeT<K,V>* nd) const;
	
	//recursive helper functions for search(range), values, and keys
	void search_subtree(NodeT<K,V>* nd, vector<V>& vect_values, K key_start, K key_end)const;
	void values_subtree(NodeT<K,V>* nd, vector<V>& vect_values)const;
	void keys_subtree(NodeT<K,V>* nd, vector<K>& vect_keys)const;
	
	//helper functions for printing
	int print_level(NodeT<K,V>* subtree, int target_level, int current_level)const;
	void print_in_order(NodeT<K,V>* subtree)const;
	
};

//IMPLEMENTATION
//==============

//CONSTRUCTORS

template <class K, class V>
RedBlackTree<K,V>::RedBlackTree(){
	root = NULL;
	current_size = 0;	
}

template <class K, class V>
RedBlackTree<K,V>::RedBlackTree( const RedBlackTree& cpy_tree){
	if( cpy_tree.root!= NULL){
		root = new NodeT<K,V>(cpy_tree.root);
		copy_subtree( root, cpy_tree.root);
		current_size = cpy_tree.current_size;
	}
	else{
		root = NULL;
		current_size = 0;
	}
}

//OPERATOR

template <class K, class V>
RedBlackTree<K,V>& RedBlackTree<K,V>::operator=( const RedBlackTree& cpy_tree){
	remove_subtree(root);
	if(cpy_tree.root != NULL){
		root = new NodeT<K,V>(cpy_tree.root);
		copy_subtree( root, cpy_tree.root);
		current_size = cpy_tree.current_size;
	}
	else{
		root = NULL;
		current_size=0;
	}
	return *this;	
}

//DESTRUCTOR

template <class K, class V>
RedBlackTree<K,V>::~RedBlackTree(){
		if( root != NULL){
			remove_subtree(root->left);
			remove_subtree(root->right);
			delete root;
		}
}

//SETTERS

template <class K, class V>
bool RedBlackTree<K,V>::insert(K key, V val){
	if(root == NULL){
		current_size++;
		root = new NodeT<K,V>(key , val);
		//root->isBlack = true;
	}
	else{
		NodeT<K,V>* x = BST_insert(key,val);
		NodeT<K,V>* b = x;
		
		x->isBlack = false;
		while ( x!=root && x->parent->isBlack == false ){ //itterates untill root or untill
			//a black child is reached
			if((x->parent->parent!= NULL)
				&& x->parent == x->parent->parent->left){ 
			
				//if x's parent is a left child
				
				NodeT<K,V>* y = x->parent->parent->right; //"uncle" of x
				
				if ( y != NULL && y->isBlack == false){ //same as x's parent
					x->parent->isBlack = true;
					y->isBlack = true;
					x->parent->parent->isBlack = false;
					x = x->parent->parent;
				}
				else { // y is a null pointer, otherwise the bh property is wrong
					if( x == x->parent->right ){
						x = x->parent;
						left_rotate(x);
					}
					x->parent->isBlack = true;
					x->parent->parent->isBlack = false;
					right_rotate(x->parent->parent);
					
				}
				
			
			}
			else if( x->parent->parent!= NULL){
				//x's parent is a right child
				NodeT<K,V>* y = x->parent->parent->left; // "uncle of x
				
				if( y != NULL && y->isBlack == false){ //same as x's parent
					x->parent->isBlack = true;
					y->isBlack = true;
					x->parent->parent->isBlack = false;
					x = x->parent->parent;
				}
				else{ //y is a null pointer, otherwise the rh property is wrong
					if(x == x->parent->left){
						x = x->parent;
						right_rotate(x);
					}
					x->parent->isBlack = true;
					x->parent->parent->isBlack = false;
					left_rotate(x->parent->parent);
				}
			}
		}
		//end of while
	}
	
	root->isBlack = true;
	return true;	
}

template <class K, class V>
bool RedBlackTree<K,V>::remove(K key){
	NodeT<K,V>* temp = root;
	while( temp != NULL && temp->key != key ){
		if(temp->key > key){
			temp = temp->left;
		}else{
			temp = temp->right;
		}
	}
	if(temp == NULL){
		return false;	
	}
	remove(temp);
	return true;
	
}

//GETTERS

template <class K, class V>
bool RedBlackTree<K,V>::search( K key ) const{
	NodeT<K,V>* nd = root;
	bool found = false;
	while(nd != NULL && found == false){
		if(nd->key == key){
			found = true;	
		}
		else if(nd->key > key){ // key argument is smaller
			nd = nd->left;	
		}
		else{
			nd = nd->right;	
		}
	}
	return found;
}

template <class K, class V>
vector<V> RedBlackTree<K,V>::search( K key_start, K key_end) const{
	//accending key order
	
	vector<V> vect_values;
	if(key_start <= key_end){
		search_subtree(root, vect_values, key_start, key_end);
	}
	
	return vect_values;	
}

template <class K, class V>
vector<V> RedBlackTree<K,V>::values() const{
	//accending key order
	vector<V> vect_values;
	values_subtree(root, vect_values );
	return vect_values;
}

template <class K, class V>
vector<K> RedBlackTree<K,V>::keys() const{
	//stub
	vector<K> vect_keys;
	keys_subtree(root, vect_keys);
	return vect_keys;
}

template <class K, class V>
int RedBlackTree<K,V>::size() const{
	return current_size;
}

template <class K, class V>
NodeT<K,V>* RedBlackTree<K,V>::getRoot()const{
	return root;	
}


//HELPER FUNCTIONS

template <class K, class V>
void RedBlackTree<K,V>::copy_subtree(NodeT<K,V>* current_nd, const NodeT<K,V>* copy_nd){
	//current_nd already has the data of copy_nd
	//we just need to copy its children
	if(copy_nd->left != NULL){
		current_nd->left = new NodeT<K,V>(copy_nd->left);
		current_nd->left->parent = current_nd;
		copy_subtree(current_nd->left, copy_nd->left);
	}
	if(copy_nd->right != NULL){
		current_nd->right = new NodeT<K,V>(copy_nd->right);
		current_nd->right->parent = current_nd;
		copy_subtree(current_nd->right, copy_nd->right);
	}
	//implicit base case, both of copy_nd's children are null pointers
}



//level-order print of tree,

template <class K, class V>
void RedBlackTree<K,V>::print_levels() const{
		if(root!= NULL){
			cout << root->key << "-" << root->value << "  ";
			cout << endl;
			int printed = 1;
			int x = 1;
			while(printed != 0){
				printed = 0;
				printed += print_level(root,x,0);
				x++;
				cout << endl;
				
			}
		}
}

template <class K, class V>
void RedBlackTree<K,V>::print_in_order()const{
	print_in_order(root);	
}

//NOTE:wont pass null node
template <class K, class V>
NodeT<K,V>* RedBlackTree<K,V>::BST_insert( K key , V val){
	NodeT<K,V>* temp = root;
	NodeT<K,V>* p = NULL;
	bool is_left_child = false;
	
	//find the correct place to put the new node
	while( temp != NULL ){
		if(key < temp->key){
			p = temp;
			temp = temp->left;
			is_left_child = true;
		}
		else {
			p = temp;
			temp = temp->right;
			is_left_child = false;
		}		
	}
	
	NodeT<K,V>* new_node = new NodeT<K,V>(key,val);
	
	//put the new node in the tree
	if(is_left_child){
		p->left = new_node;
		new_node->parent = p;
	}
	else{
		p->right = new_node;
		new_node->parent = p;
	}
	current_size++;
	return new_node;	
}

template <class K, class V>
void RedBlackTree<K,V>::left_rotate( NodeT<K,V>* nd ){
	
	bool is_left_child = (nd!=root && nd == nd->parent->left);
	NodeT<K,V>* temp = nd->right;
	
	
	if(temp!= NULL){
		nd->right = temp->left;
		if(nd->right != NULL){
			nd->right->parent = nd;	
		}
		temp->left = nd;
		
		if(nd == root){
			root = temp;
			temp->parent = NULL;
		}
		else if(is_left_child){
			nd->parent->left = temp;
			temp->parent = nd->parent;
		}
		else{
			nd->parent->right = temp;
			temp->parent = nd->parent;
		}
		nd->parent = temp;
	}
	
}

template <class K, class V>
void RedBlackTree<K,V>::right_rotate( NodeT<K,V>* nd){
	
	bool is_left_child = (nd != root && nd == nd->parent->left);
	NodeT<K,V>* temp = nd->left;
	
	
	if(temp!= NULL){
		nd->left = temp->right;
		if(nd->left != NULL){
			nd->left->parent = nd;
		}
		temp->right = nd;
		
		
		if(nd == root){
			root = temp;
			temp->parent = NULL;
		}
		else if(is_left_child){
			nd->parent->left = temp;
			temp->parent = nd->parent;
		}
		else{
			nd->parent->right = temp;
			temp->parent = nd->parent;
		}
		nd->parent = temp;
		
	}
	
		
}

template <class K, class V>
void RedBlackTree<K,V>::RedBlack_fix(NodeT<K,V>* fix_nd, NodeT<K,V>* parent_nd, bool is_left){
	while( fix_nd != root && parent_nd!=NULL && (fix_nd == NULL || fix_nd->isBlack == true)){
		if(is_left){ //if fix_nd is a left child
			NodeT<K,V>* sibling_nd = parent_nd->right;
			if(sibling_nd->isBlack == false){
				cout << "BLOCK !" << endl;
				sibling_nd->isBlack = true;
				parent_nd->isBlack = false;
				left_rotate(parent_nd);
				sibling_nd = parent_nd->right;
			}
			if((sibling_nd->left == NULL || sibling_nd->left->isBlack == true) && (sibling_nd->right == NULL
				|| sibling_nd->right->isBlack == true)){
				cout << "BLOCK @" << endl;
				sibling_nd->isBlack = false;
				fix_nd = parent_nd;
				parent_nd = fix_nd->parent;
			}
			else{
				cout << "BLOCK #" << endl;
				if(sibling_nd->right == NULL || sibling_nd->right->isBlack == true){
					sibling_nd->left->isBlack = true;
					sibling_nd->isBlack = false;
					right_rotate(sibling_nd);
					sibling_nd = parent_nd->right;
				}
				sibling_nd->isBlack = parent_nd->isBlack;
				parent_nd->isBlack = true;
				sibling_nd->right->isBlack = true;
				left_rotate(parent_nd);
				fix_nd = root;
				parent_nd = NULL;
			}
		}
		else{ // if fix_nd is a right child
			NodeT<K,V>* sibling_nd = parent_nd->left;
			if(sibling_nd->isBlack == false){
				sibling_nd->isBlack = true;
				parent_nd->isBlack = false;
				right_rotate(parent_nd);
				sibling_nd = parent_nd->left;
			}
			if((sibling_nd->left == NULL || sibling_nd->left->isBlack == true) && (sibling_nd->right == NULL
				|| sibling_nd->right->isBlack == true)){
				sibling_nd->isBlack = false;
				fix_nd = parent_nd;
				parent_nd = fix_nd->parent;
				
			}
			else{
				if(sibling_nd->left == NULL || sibling_nd->left->isBlack == true){
					sibling_nd->right->isBlack = true;
					sibling_nd->isBlack = false;
					left_rotate(sibling_nd);
					sibling_nd = parent_nd->left;
				}
				sibling_nd->isBlack = parent_nd->isBlack;
				parent_nd->isBlack = true;
				sibling_nd->left->isBlack = true;
				right_rotate(parent_nd);
				fix_nd = root;
				parent_nd = NULL;
			}
		}
	}
	if(fix_nd != NULL){
		fix_nd->isBlack = true;
	}
}

template <class K, class V>
void RedBlackTree<K,V>::remove_subtree(NodeT<K,V>* subtree){
	if( subtree != NULL){
		remove_subtree(subtree->left);
		remove_subtree(subtree->right);
		delete subtree;
	}
}

template <class K, class V>
void RedBlackTree<K,V>::remove(NodeT<K,V>* nd){
	if(nd != NULL){
		NodeT<K,V>* remove_nd = NULL; //node to be removed
		NodeT<K,V>* temp = NULL; //node to replace remove_nd
		NodeT<K,V>* temp_parent = NULL;
		bool temp_is_left;
			
		if(nd->left == NULL || nd->right == NULL){
			remove_nd = nd;
			
		}
		else{
			remove_nd = predecessor(nd);
		}
		if(remove_nd->left != NULL){
			temp = remove_nd->left;
			
		}
		else{
			temp = remove_nd->right;
		}
		temp_parent = remove_nd->parent; // detach temp from remove_node
		if(temp != NULL){
			temp->parent = temp_parent;	
		}
		
		if(remove_nd -> parent == NULL){ // remove_node is the root
			root = temp;
			temp->parent = NULL;
			temp_parent = NULL;
		}
		else{
			//attatch temp to y's parent
			if(remove_nd == remove_nd->parent->left){
				remove_nd->parent->left = temp;
				temp_parent = remove_nd->parent;
				if(temp != NULL){
					temp->parent = temp_parent;	
				}
				temp_is_left = true;
			}
			else{
				remove_nd->parent->right = temp;
				temp_parent = remove_nd->parent;
				if(temp != NULL){
					temp->parent = temp_parent;	
				}
				temp_is_left = false;
			}
		}
		if(remove_nd != nd){ // ie remove_nd has conceptualy, been moved up
			//replace
			nd->key = remove_nd->key;
			nd->value = remove_nd->value;
		}
		if( remove_nd->isBlack == true){
			RedBlack_fix(temp,temp_parent,temp_is_left);	
		}
		delete remove_nd;
	}
}

template <class K, class V>
NodeT<K,V>* RedBlackTree<K,V>::predecessor(NodeT<K,V>* nd) const{
	NodeT<K,V>* temp = nd->left;
	
	while(temp->right != NULL){
		temp = temp->right;	
	}
	return temp;
}

template <class K, class V>
void RedBlackTree<K,V>::search_subtree(NodeT<K,V>* nd, vector<V>& vect_values, K key_start, K key_end)const{
	if(nd != NULL ){ //implicit base case: nd == NULL
		//in order
		search_subtree(nd->left, vect_values, key_start, key_end);
		if(nd->key >= key_start && nd->key <= key_end){
			vect_values.push_back(nd->value);	
		}
		search_subtree(nd->right, vect_values, key_start, key_end);
	}
}

template <class K, class V>
void RedBlackTree<K,V>::values_subtree(NodeT<K,V>* nd, vector<V>& vect_values)const{
	if(nd!=NULL){ //implicit base case: nd == NULL
		//in-order
		values_subtree(nd->left, vect_values);
		vect_values.push_back(nd->value);
		values_subtree(nd->right, vect_values);
	}
}

template <class K, class V>
void RedBlackTree<K,V>::keys_subtree(NodeT<K,V>* nd, vector<K>& vect_keys)const{
	if (nd!=NULL){ //implicit base case: nd == NULL
		//in-order
		keys_subtree(nd->left, vect_keys);
		vect_keys.push_back(nd->key);
		keys_subtree(nd->right, vect_keys);
	}
}

template <class K, class V>
int RedBlackTree<K,V>::print_level(NodeT<K,V>* subtree,int target_lvl, int current_lvl) const{
	if(subtree == NULL) {
		for(int k = 0; k < (int)pow(2.0,(double)(target_lvl-current_lvl)); k++){
			cout << "#-# ";
		}
		return 0;
	}
	else if(current_lvl == target_lvl-1){
		int count = 0;
		//if left child exist, print it
		if(subtree->left != NULL){
			if( subtree->left->isBlack == false ){
				cout << "*";	
			}
			cout << subtree->left->key << "-" << subtree->left->value << " ";
			count ++;
		}
		else{
			cout << "#-# ";	
		}
		if(subtree->right != NULL){
			if( subtree->right->isBlack == false ){
				cout << "*";	
			}
			cout << subtree->right->key << "-" << subtree->right->value << " ";
			count++;
		}
		else{
			cout << "#-# ";
		}
		return count;
	}
	else{
		int count = print_level(subtree->left,target_lvl, current_lvl+1);
		count += print_level(subtree->right,target_lvl, current_lvl+1);
		return count;
	}
}

template <class K, class V>
void RedBlackTree<K,V>::print_in_order(NodeT<K,V>* subtree)const{
	if(subtree!=NULL){
		print_in_order(subtree->left);
		cout << subtree->key << "-" << subtree->value << endl;
		print_in_order(subtree->right);
	}
}



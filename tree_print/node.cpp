#include "node.hpp"
#include <cstdlib>

/*
class node{
private:
	int data;
	node* left;
	node* right;
	
};
*/

node::node(){
	data=0;	
}
node::node(int i){
	data = i;	
}

node::~node(){
	if(left != NULL){
		delete left;
		left = NULL;
	}
	if(right != NULL){
		delete right;
		right == NULL;
	}
}
int node::getData(){
	return data;
}

node* node::getLeft(){
	return left;	
}

node* node::getRight(){
	return right;	
}


void node::setChilds(node* nleft, node* nright){
	if(nleft != NULL){
		left = nleft;
	}
	if(nright != NULL){
		right = nright;	
	}
}

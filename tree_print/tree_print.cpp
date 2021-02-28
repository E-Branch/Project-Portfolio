#include <iostream>
#include "node.hpp"
using std::cout;
using std::endl;

void pre_order(node* t){
	if(t==NULL)return;
	cout << t->getData();
	if(t->getLeft() != NULL ){
		cout << ", ";
		pre_order(t->getLeft());
	}
	if(t->getRight() != NULL ){
		cout<<", ";
		pre_order(t->getRight());
	}
	return;
}

void in_order(node* t){
	if(t==NULL)return;
	if(t->getLeft()!= NULL ){
		in_order(t->getLeft());
		cout << ", ";
	}
	cout << t->getData();
	if(t->getRight()!= NULL ){
		cout << ", ";
		in_order(t->getRight());
	}
	return;
}

void post_order(node* t){
	if(t==NULL)return;
	if(t->getLeft()!=NULL){
		post_order(t->getLeft());
		cout << ", ";
	}
	if(t->getRight()!=NULL){
		post_order(t->getRight());
		cout << ", ";
	}
	cout << t->getData();
}

int main(){
	node* tree = new node(7);
	tree->setChilds(new node(3),new node(2));
	(tree->getLeft())->setChilds(new node(4),NULL);
	(tree->getRight())->setChilds(new node(21), new node(13));
	cout << "pre order: ";
	pre_order(tree);
	cout << endl << "in order: ";
	in_order(tree);
	cout << endl << "post order: ";
	post_order(tree);
	cout<<endl;
	delete tree;
}

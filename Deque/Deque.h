#pragma once
#include <stdexcept>
#include <iostream>

template <class T>
class Node{
public:
	T data;
	Node<T>* previous;
	Node<T>* next;

	//constructor
	Node(T val) : data(val) , previous(NULL) , next(NULL) {};
		
};

template <class T>
class Deque{
private:
	Node<T>* front;
	Node<T>* back;
	
public:
	//constructors
	Deque() : front(NULL) , back(NULL) {}; //creates an empty Deque object
	Deque(const Deque<T>& toCopy); //creates a new object that is a deep copy of toCopy
	
	//operators
	Deque<T>& operator=(const Deque<T>& toCopy); //deallocs old value in caller and deep copies toCopy
	
	//destructor
	~Deque(); //deallocates all memory
	
	//setters
	void insertFront(T val);
	void insertBack(T val);
	
	//getters
	T removeFront();
	T removeBack();
	T peekFront() const;
	T peekBack() const;
	bool empty() const;
	int size() const;
	
	//other
	void print() const;
};



//constructor
template <class T> 
Deque<T>::Deque( const Deque<T>& toCopy ){
	front = NULL;
	back = NULL;
	
	//iterate through the other deque, copying each VALUE into the calling object
	Node<T>* temp = toCopy.front;
	while(temp != NULL){
		insertBack(temp->data);
		temp = temp->next;
	}
}

//opperator

template <class T>
Deque<T>& Deque<T>::operator=( const Deque<T>& toCopy ){
	//deallocate all memory in the doubly linked list
	Node<T>* temp1 = front;
	while(temp1 != NULL){
			Node<T>* temp2 = temp1;
			temp1 = temp1->next;
			delete temp2;
	}
	//copy the new deque into the calling object
	front = NULL;
	back = NULL;
	Node<T>* temp = toCopy.front;
	while(temp != NULL){
		insertBack(temp->data);
		temp = temp->next;
	}
	
	return *this;	
}

//destructor
template <class T>
Deque<T>::~Deque(){
	//iterate throught the deque, deallocating all nodes
	Node<T>* temp1 = front;
	while(temp1 != NULL){
		Node<T>* temp2 = temp1;
		temp1 = temp1->next;
		delete temp2;
	}
}

//setters
template <class T>
void Deque<T>::insertFront(T val){
	//if the deque is empty, the new element will be the front and back
	if( empty() ){
		Node<T>* newnode = new Node<T>(val);
		front = newnode;
		back = newnode;
	}
	else{
		//else if the deque is not empty
		//create a new node
		Node<T>* newnode = new Node<T>(val);
		
		//the new node points (with NEXT) to the front
		newnode->next = front;
		
		// the front points (with PREVIOUS) to the new node
		front->previous = newnode;
		
		//the new node is now the front
		front = newnode;
		
	}
}

template <class T>
void Deque<T>::insertBack(T val){
	//if the deque is empty, the new element will be the front and the back
	if( empty() ){
		Node<T>* newnode = new Node<T>(val);
		front = newnode;
		back = newnode;
	}
	else{
		//else if the deque is not empty, create a new node
		Node<T>* newnode = new Node<T>(val);
		
		//the new node points (with PREVIOUS) to back
		newnode->previous = back;
		
		//back points (NEXT) to the new node
		back->next = newnode;
		
		//the new node is now the back
		back = newnode;
	}
}

//getters
template <class T>
T Deque<T>::removeFront(){
	//in empty, throw runntime error
	if ( empty() ){
		throw std::runtime_error("error:empty deque");	
	}
	
	//else if one element
	if ( front == back ){
		//record the data in the node
		int val = front->data;
		
		//idk why the next line caused it to have too many frees, weird
		/*
		delete front;
		*/
		
		//set both the front and the back to NULL
		front == NULL;
		back == NULL;
		
		//return the value
		return val;
	}
	
		
	//get the value at the first node
	int val = 0;
	val = front->data;
	
	//save the pointer to the first node
	Node<T>* temp = front;
	
	//make the next node the front
	front = front->next;
	
	//set the new fronts backwards pointer to null
	front->previous = NULL;
	
	//dealloc the node
	delete temp;
	
	//return the data
	return val;
}

template <class T>
T Deque<T>::removeBack(){
	//if deque is empty, throw runtime error
	if( empty() ){
		throw std::runtime_error("error:empty deque");
	}
	
	//else if one element
	if ( front == back ){
		//save the value stored
		int val = front->data;
		
		//set both the front and back to NULL
		front == NULL;
		back == NULL;
		
		//return the value
		return val;
	}
	
	//get the value at the last node
	int val;
	val = back->data;
	
	//save the pointer to the last node
	Node<T>* temp = back;
	
	//make the second to last node the last node
	back = back->previous;
	
	//set the new backs forward pointer to null
	back->next = NULL;
	
	//dealloc the node
	delete temp;
	
	//return the value
	return val;
	
}

template <class T>
T Deque<T>::peekFront() const{
	//if the Deque is empty, throw an error
	if( empty() ) {
		throw std::runtime_error("error:empty deque");
	}
	
	//otherwise, return the value stored in front
	return front->data;
}

template <class T>
T Deque<T>::peekBack() const{
	//if the deque is empty, throw a runtime error
	if( empty() ){
		throw std::runtime_error("error:empty deque");
	}
	
	//otherwise, return the value stores in back
	return back->data;
}

template <class T>
bool Deque<T>::empty() const{
	//if both the front and back are null
	//if only one of then was it would be messes up, but just in case
	if( front == NULL && back == NULL){
		return true;
	}
	return false;
}

template <class T>
int Deque<T>::size() const{
	//iterate through the deque, incrementing the variable
	int count = 0;
	Node<T>* temp = front;
	while(temp != NULL){
		count++;
		temp = temp->next;
	}
	
	//return the variable
	return count;
}

//for my testing, prints out the entire deque
template <class T>
void Deque<T>::print() const{
	Node<T>* temp = front;
	while(temp != NULL){
		std::cout << "  " << temp->data;
		temp = temp->next;
	}
}




















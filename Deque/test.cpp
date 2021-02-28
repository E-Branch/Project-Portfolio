#include "Deque.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
	cout << "compiled correctly!" << endl;
	//version before conversion to template
	
	//testing node class
	cout << "test node constructor and destructor: " << endl;
	Node<int>* testnode = new Node<int>(3);
	cout << "node data: " << testnode->data << " node pointers: " << testnode->next << ",";
	cout << testnode->previous << endl;
	cout << "destructor: " ;
	delete testnode;
	testnode = NULL;
	cout << "the computer didnt break, so thats good!" << endl;
	
	//testing Deque class
	cout << "TESTING DEQUE CLASS" << endl;
	Deque<int> test1;
	Deque<int>test2;
	
	cout << " testing insertFront(int val): " << endl;
	test1.insertFront(4);
	test1.insertFront(6);
	test1.insertFront(3);
	test1.insertFront(8);
	test1.insertFront(2);
	test1.insertFront(3);
	cout<< "  expected deque:  3  2  8  3  6  4  actual deque:";
	test1.print();
	cout << endl;
	
	cout << " testing insertBack: " << endl;
	test2.insertBack(6);
	test2.insertBack(3);
	test2.insertBack(8);
	test2.insertBack(2);
	test2.insertBack(3);
	test2.insertFront(4);
	cout << "  expected deque:  4  6  3  8  2  3  actual deque:";
	test2.print();
	cout<<endl;
	
	cout << " testing copy constructor: " << endl;
	cout << " case 1: copy non-empty deque" << endl;
	Deque<int> test3(test2);
	cout << "  expected deque:  4  6  3  8  2  3  actual deque:";
	test3.print();
	cout<<endl;
	
	cout << " case2 2: copy empty deque" << endl;
	Deque<int> test4;
	Deque<int> test5(test4);
	cout << "  expected deque:  actual deque:";
	test5.print();
	cout<<endl;
	
	cout<< " testing = operator" << endl;
	
	cout<< " case 1: copy non-empty deque" << endl;
	test5 = test2;
	cout << "  expected deque:  4  6  3  8  2  3  actual deque:";
	test5.print();
	cout<<endl;
	
	cout << " case 2: copy empty deque" << endl;
	test5 = test4;
	cout << "  expected deque:  actual deque:";
	test5.print();
	cout << endl;
	
	cout << "case 3: copy self" << endl;
	cout << "  expected deque:";
	test5.print();
	cout<< "actual deque:";
	test5 = test5;
	test5.print();
	cout<<endl;
	
	cout << " testing remove front" << endl;
	cout << " case 1, non-empty deque" << endl;
	int c = 0;
	c = test2.removeFront();
	cout << "  expected deque:  6  3  8  2  3  actual deque:";
	test2.print();
	cout << endl;
	cout << "removed value: " << c << endl;
	
	cout << " case 2, empty deque" << endl;
	Deque<int> test6;
	try{
		test6.removeFront();
	}catch(std::exception& e){
		cout << e.what() << endl;
	}
	
	cout << " testing remove back"<<endl;
	c = test2.removeBack();
	cout << "  expected deque:  6  3  8  2  actual deque: ";
	test2.print();
	cout << endl;
	cout << "removed value: " << c << endl;
	
	cout << " testing peek front";
	c = test2.peekFront();
	cout << "  expected result: 6 , actual result: " << c << endl;
	
	cout << " testing peek back";
	c = test2.peekBack();
	cout << " expected result: 2, actual result: " << c << endl;
	
	cout << "testing array is not changed: ";
	test2.print();
	cout<<endl;
	
	cout << " testing empty()" << endl;
	cout << " case 1, non-empty deque" << endl;
	bool t;
	t = test2.empty();
	cout << "   expected result: 0, acutal result: " << t << endl;
	
	cout << " case 2, empty deque" << endl;
	t = test6.empty();
	cout << "   expected result: 1 , actual result: " << t << endl;
	
	
	cout << " testing size" << endl;
	cout << " case 1, non-empty deque";
	int s;
	s = test2.size();
	cout << "expected result: 4, actual result: " << s << endl;
	
	cout << " case 2, empty deque" << endl;
	s=test6.size();
	cout << "expected result: 0, actual result: " << s << endl;
	
	
	cout << "FURTHER TEsT || REMOVE:" << endl;
	Deque<char> char1;
	char1.insertFront('s');
	char1.insertBack('g');
	char1.insertBack('%');
	char1.insertFront('2');
	char1.insertBack('*');
	cout << "original array:";
	char1.print();
	cout << endl;
	cout << "removing from back: " << char1.removeBack() << endl;
	cout << "removing from front: " << char1.removeFront() << endl;
	cout << "removing from front: " << char1.removeFront() << endl;
	cout << "removing from back: " << char1.removeBack() << endl;
	cout << "removing from back: " << char1.removeBack() << endl;
	
	cout << endl;
	return 0;
}

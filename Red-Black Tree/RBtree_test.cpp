#include "RedBlackTree.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main(){
	cout << "test drive for RedBlackTrees:" << endl;
	cout << "=============================" << endl;
	
	/*
	RedBlackTree<int,int> rb1;
	rb1.root = new NodeT<int,int>(17,1);
	NodeT<int,int>* x = rb1.BST_insert(4,1);
	rb1.BST_insert(23,1);
	rb1.BST_insert(5,1);
	
	rb1.print_levels();
	
	cout << "left rotate(3)" << endl;
	
	rb1.left_rotate(x);
	
	rb1.print_levels();
	
	cout << "right rotate(4)" << endl;
	x = x->parent;
	rb1.right_rotate(x);
	
	
	rb1.print_levels();
	
	*/
	
	
	
	
	cout << "tree3:" << endl;
	
	RedBlackTree<int,int> rb3;
	
	rb3.insert(23,9);
	rb3.insert(32,2);
	rb3.insert(8,44);
	rb3.insert(12,5);
	rb3.insert(3,4);
	
	cout << "inserted: 23, 32, 8, 12, 3" << endl;
	cout << "level-order print:" << endl;
	rb3.print_levels();
	
	
	cout << "find 3" << endl;
	cout << rb3.search(3) << endl;
	
	
	cout << "keys:" << endl;
	vector<int> kys = rb3.keys();
	for(int k=0 ; k<kys.size() ; k++){
		cout << " " << kys.at(k);	
	}
	cout << endl;
	
	
	cout << "find, 1-14" << endl;
	kys = rb3.search(1,14);
	
	for(int k=0 ; k<kys.size() ; k++){
		cout << " " << kys.at(k);	
	}
	cout << endl;
	
	
	cout << "values:" << endl;
	vector<int> vals = rb3.values();
	
	for(int k = 0; k< vals.size() ; k++){
		cout << " " << vals.at(k);	
	}
	cout << endl;
	
	
	
	cout << "copying tree" << endl;
	RedBlackTree<int,int> rb4(rb3);
	
	cout << "level-order print" << endl;
	rb4.print_levels();
	
	cout << "removing 8 from copy" << endl;
	rb4.remove(8);
	
	cout << "original:" << endl;
	rb3.print_levels();
	
	cout << endl << "copy:" << endl;
	rb4.print_levels();
	
	cout << "removing 32 from copy" << endl;
	rb4.remove(32);
	
	cout << "original:" << endl;
	rb3.print_levels();
	
	cout << endl << "copy:" << endl;
	rb4.print_levels();
	
	cout << "removing 4 from copy" << endl;
	rb4.remove(4);
	
	cout << "original:" << endl;
	rb3.print_levels();
	
	cout << endl << "copy:" << endl;
	rb4.print_levels();
	
	cout << "removing 23 from copy" << endl;
	rb4.remove(23);
	
	cout << "original:" << endl;
	rb3.print_levels();
	
	cout << endl << "copy:" << endl;
	rb4.print_levels();
	
	
	cout << "testing template: int, string" << endl;
	RedBlackTree<int , string> str1;
	
	str1.insert(5, "red");
	str1.insert(16 , "hello world!");
	str1.insert(2, "Jerry");
	str1.insert(12, "14");
	str1.insert(3, "door");
	
	cout << "printing tree:" << endl;
	str1.print_levels();
	
	cout << "removing 2:" << endl;
	str1.remove(2);
	str1.print_levels();
	
	
	
	cout << "find 3" << endl;
	cout << str1.search(3) << endl;
	
	
	cout << "keys:" << endl;
	kys = str1.keys();
	for(int k=0 ; k<kys.size() ; k++){
		cout << " " << kys.at(k);	
	}
	cout << endl;
	
	
	cout << "find, 1-14" << endl;
	vector<string> strings = str1.search(1,14);
	
	for(int k=0 ; k<strings.size() ; k++){
		cout << " " << strings.at(k);	
	}
	cout << endl;
	
	
	cout << "values:" << endl;
	strings = str1.values();
	
	for(int k = 0; k< strings.size() ; k++){
		cout << " " << strings.at(k);	
	}
	cout << endl;
	
	cout << "copying tree using '=' " << endl;
	RedBlackTree<int, string> str2;
	
	str2.insert(4, "this");
	str2.insert(17, "you");
	str2.insert(14, "should");
	str2.insert(13, "not");
	str2.insert(6, "see");
	
	str2 = str1;
	
	str2.print_levels();
	cout << "size(1):" << str1.size() << endl;
	cout << "size(2):" << str2.size() << endl;
	
	str2 = RedBlackTree<int, string>();
	
	str2.insert(36, "book");
	str2.insert(14, "red");
	str2.insert(4, "Kagerou");
	str2.insert(12, "12");
	str2.insert(17, "grey");
	str2.insert(2, "integer");
	str2.insert(14, "lost");
	
	str2.print_levels();
	
	cout << endl;
	
	RedBlackTree<string,string> str3;
	
	str3.insert("Ross","Bob");
	str3.print_levels();
	cout << endl;
	
	str3.insert("Joe" , "Mama");
	str3.print_levels();
	cout << endl;
	
	str3.insert("Smith", "Karen");
	str3.print_levels();
	cout << endl;
	
	str3.insert("Clark", "Kent");
	str3.print_levels();
	cout << endl;
	
	str3.insert("Dead" , "Memes");
	str3.print_levels();
	cout << endl;
	
	str3.insert("Branch","Emily");
	str3.print_levels();
	cout << endl;
	
	str3.insert("Harolds","Dennis");
	
	str3.print_levels();
	cout << endl;
	
	cout << endl << str3.size();
	
	cout << "removing smith " << endl;
	
	str3.remove("Smith");
	cout << endl;
	
	str3.print_levels();
	
	cout << "search : Sharol:";
	cout << str3.search("Sharol") << endl;
	cout << "search : Branch:";
	cout << str3.search("Branch") << endl;
	
	cout << "search : carol- joe" << endl;
	vector<string> strings2 = str3.search("Carol","Joe");
	for(int k = 0; k<strings2.size(); k++){
		cout << " " << strings2.at(k);
	}
	cout << endl << "values" << endl;
	strings2 = str3.values();
	for(int k = 0; k<strings2.size(); k++){
		cout << " " << strings2.at(k);
	}
	cout << endl << "keys" << endl;
	strings2 = str3.keys();
	for(int k = 0; k<strings2.size(); k++){
		cout << " " << strings2.at(k);
	}
	cout << endl;
	
	
	
	
	return 0;
}

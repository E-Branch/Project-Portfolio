#include "cmpt225sort.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main(){
	
	cout << "INSERTION SORT:" << endl << endl;
	
	char avg[] = { 'c', '7', 'h', 'a', 'g' , 'z' , 'K' };
	int len = 7;
	cout << "average case:" << endl;
	cout << "original string: ";
	for(int k = 0; k < len; k++){
		cout << " " << avg[k];	
	}
	cout << endl << "len=" << len << endl;
	
	int n = insertionsort<char>(avg,len);
	
	cout << "after sorting: ";
	for(int k = 0; k < len; k++){
		cout << " " << avg[k];	
	}
	cout << endl;
	cout << "n= " << n << endl;
	
	
	cout << "worst case" << endl;
	int worst[] = { 9 , 7 , 6 , 3 , 2 , 1 , 0 };
	cout << "original string: ";
	for(int k = 0; k < len; k++){
		cout << " " << worst[k];	
	}
	cout << endl << "len=" << len <<  endl;
	
	n = insertionsort<int>(worst,len);
	
	cout << "after sorting: ";
	for(int k = 0; k < len; k++){
		cout << " " << worst[k];	
	}
	cout << endl;
	cout << "n= " << n << endl;
	
	
	cout << "best case:" << endl;
	int best[] = { 0 , 1 , 2 , 3 , 6 , 7 , 9 };
	for(int k = 0; k < len; k++){
		cout << " " << best[k];	
	}
	cout << endl << "len=" << len << endl;
	
	n = insertionsort<int>(best,len);
	
	for(int k = 0; k < len; k++){
		cout << " " << best[k];	
	}
	cout << endl;
	cout << "n= " << n << endl;
	
	
	
	cout << "QUICKSORT" << endl << endl;
	
	int avg2[] = { 2 , 6 , 3 , 9 , 7 , 1 , 0 };
	int len2 = 7;
	cout << "average case:" << endl;
	cout << "original string: ";
	for(int k = 0; k < len2; k++){
		cout << " " << avg2[k];	
	}
	cout << endl << "len=" << len2 << endl;
	
	int n2 = quicksort<int>(avg2,len2);
	
	cout << "after sorting: ";
	for(int k = 0; k < len2; k++){
		cout << " " << avg2[k];	
	}
	cout << endl;
	cout << "n2= " << n2 << endl;
	
	
	cout << "worst2 case" << endl;
	int worst2[] = { 9 , 7 , 6 , 3 , 2 , 1 , 0 };
	cout << "original string: ";
	for(int k = 0; k < len2; k++){
		cout << " " << worst2[k];	
	}
	cout << endl << "len=" << len2 << endl;
	
	n2 = quicksort<int>(worst2,len2);
	
	cout << "after sorting: ";
	for(int k = 0; k < len2; k++){
		cout << " " << worst2[k];	
	}
	cout << endl;
	cout << "n2= " << n2 << endl;
	
	
	cout << "best2 case:" << endl;
	int best2[] = { 0 , 1 , 2 , 3 , 6 , 7 , 9 };
	for(int k = 0; k < len2; k++){
		cout << " " << best2[k];	
	}
	cout << endl << "len=" << endl;
	
	n2 = quicksort<int>(best2,len2);
	
	for(int k = 0; k < len2; k++){
		cout << " " << best2[k];	
	}
	cout << endl;
	cout << "n2= " << n2 << endl;
	
	cout << " TESTING WITH STRINGS" << endl;
	
	string str1[] = { "red" , "green", "blue", "purple", "yellow", "brown" , "cyan" , "purple" , "sea green"};
	int strlen = 9;
	cout << "before sorting:";
	for(int k = 0; k< strlen; k++){
		cout << " " << str1[k];
	}
	cout << endl << "len=" << strlen << endl;
	
	int strn = quicksort<string>(str1,strlen);
	
	cout << "after sorting:";
	for(int k = 0; k< strlen; k++){
		cout << " " << str1[k];
	}
	cout << endl;
	cout << "n=" << strn << endl;
	
	
	cout << "SHELL SORT" << endl;
	
	string shell1[] = { "red", "halo" , "snakes", "knitting" , "rumble" , "tumble" , "roll" , "blue"};
	int shell2[] = { 4, 3, 2, 8, 4, 9, 3};
	int s1len = 8;
	int s2len = 7;
	
	cout << "before sorting:";
	for( int k = 0; k< s1len; k++){
		cout << " " << shell1[k];	
	}
	cout << endl << "len=" << s1len << endl;
	
	int s1n = shellsort<string>(shell1,s1len);
	
	cout << "after sorting:";
	for( int k = 0; k< s1len; k++){
		cout << " " << shell1[k];	
	}
	cout << endl << "n=" << s1n << endl;
	
	cout << "before sorting:";
	for(int k = 0; k<s2len; k++){
		cout << " " << shell2[k];	
	}
	cout << endl << "len=" << s2len << endl;;
	
	int s2n = shellsort<int>(shell2,s2len);
	
	cout << "after sorting:";
	for(int k = 0; k<s2len; k++){
		cout << " " << shell2[k];	
	}
	cout << endl << "n=" << s2n << endl;
	
	
	
	cout << "MERGESORT" << endl;
	double merg1[] = { 6.4, 2.8, 3.5, 9.9, 5.0 , 6.7, 2.4 , 1.1 , 7,7};
	int m1len = 9;
	
	cout<< "original array:";
	for(int k = 0; k<m1len; k++){
		cout<< " " << merg1[k];	
	}
	cout << endl << "len=" << m1len << endl;
	
	int mergn = mergesort<double>(merg1,m1len);
	
	cout << "after mergesort:";
	for(int k = 0; k<m1len;k++){
		cout << " " << merg1[k];	
	}
	cout << endl << "n=" << mergn << endl;
	
	string merg2[] = {"blue","green","seven","black","oregano","cat","Kevin" , "cheese" , "45" , "88" , "holly"};
	int m2len = 11;
	
	cout << "original array:";
	for(int k = 0; k<m2len; k++){
		cout << " " << merg2[k];	
	}
	cout << endl << "len=" << m2len << endl;
	
	mergn = mergesort<string>(merg2,m2len);
	
	cout << "after mergesort:";
	for(int k = 0; k<m2len; k++){
		cout << " " << merg2[k];	
	}
	cout << endl << "n=" << mergn << endl;
	
	
	return 0;	
}

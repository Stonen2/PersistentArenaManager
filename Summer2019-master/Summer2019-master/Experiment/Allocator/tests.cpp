//#include "TA.h"
#include "mapalloc.h"
#include <iostream>
using namespace std; 





int main() {
	int a = 5;
	int b = 3; 
	int c = 4; 
	int d = 10; 

	size_t j = sizeof(a);
	mapalloc m(j);

	int * f = static_cast <int*>(m.malloc(sizeof(b)));
	int * g = static_cast <int*>(m.malloc(sizeof(c)));
	int * h = static_cast <int*>(m.malloc(sizeof(d)));


	
	cout << &f << " F" << endl; 
	cout << &g << " G" << endl; 
	cout << &h << " D" << endl;

	//allocator a(f); 



	

	//TA test(sizeof(a)); 
	//void* t = test.start; 

	//cout << &t + 512 << "TESTING" << endl; 

	//cout << &t << endl;
	 
	//allocator a; 

	//int* p = static_cast <int*>(test.malloc(a));
	
	
	//cout << "HAHA" << endl; 
	//int s = t; 
	//int ff = p; 

	//cout << t - p << endl;
	//cout << &p;
	cout << "OBJEXT HAS BEEN BUILT";



	//cout << test.start + test.next;
	//cout << p; 
	cout << endl; 
	//cout << test.HeapSize;
	cout << endl; 

	//cout << test.next;


}
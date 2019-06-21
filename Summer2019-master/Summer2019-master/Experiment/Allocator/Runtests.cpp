#include "linkedList.h"
#include <iostream>

using namespace std; 


int main() {

	linkedList l; 
	//
	cout << endl;
	l.print();
	//cout << "Bulls";


	l.insert(2);
	l.insert(5);
	l.insert(7);
	l.insert(8);
	cout << endl;
	l.print();

	return 0; 
}
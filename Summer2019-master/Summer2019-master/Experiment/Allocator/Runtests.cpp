#include "linkedList.h"
#include <iostream>

using namespace std; 


int main() {

	linkedList l; 
	l.insert(2);
	l.insert(5);
	cout << endl;
	l.print();

	return 0; 
}
#include <iostream>
#include "CrashRecoveryBitMap.h"


using namespace std; 



int main() {


	size_t t = 8;

	CrashRecoveryBitMap m(t); 


	cout << endl; 
	cout << "-----------";
	m.print();
	m.flipbits(3);
	cout << endl; 
	m.print();
	//out << "Hello Universe";





	return 0;
};
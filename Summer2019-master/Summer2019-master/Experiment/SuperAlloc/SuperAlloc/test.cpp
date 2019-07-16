#include <iostream>
#include "MegaAlloc.h"
#include <conio.h> //for getch()
using namespace std; 


int main() {

	MegaAlloc<int> s; 

	//s.operator new(sizeof(4));
	//ss.operator new(sizeof(5));
	//cout << s.getchunk();

	cout << "here we are";
	cout << endl; 
	s.print();


	cout << "Finished";


	return 0; 

	
	


	//return 0; 
}
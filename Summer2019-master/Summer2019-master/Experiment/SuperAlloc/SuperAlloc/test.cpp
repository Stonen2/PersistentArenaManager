#include <iostream>
#include "MegaAlloc.h"
#include <conio.h> //for getch()
#include <string>
#include <cmath>
using namespace std; 


int main() {

	MegaAlloc<int> s; 

	//s.operator new(sizeof(4));
	//ss.operator new(sizeof(5));
	//cout << s.getchunk();
	int a = 19;
	int b = 200; 
	int c = 300; 
	
	void * fds = s.bitallocate(sizeof(a));
	//s.allocate();
	void* letssee = s.bitallocate(sizeof(b));
	void* comeon = s.bitallocate(sizeof(c));
	//cout << "here we are";
	void* strt = s.getstart();

	size_t temp = (size_t)strt - (size_t)fds; 

	cout << endl; 
	cout << endl; 
	cout << "PRINT"<< endl;
	s.print();
	cout << endl; 
	//cout << s.getchunk() << endl;
	//cout << s.getarenas();
	cout << endl; 
	cout << endl; 
	cout << endl; 



	//cout << "Finished";
	cout << fds << endl;
	cout << letssee << endl; 
	cout << comeon; 
	cout << endl; 
	cout << temp; 
	cout << endl; 
	cout << "FINISH";
	//int i = std::stoi("01000101", nullptr, 2);
	//cout << i; 
	
	//char sasd = "00000";
	//char* ffa = sasd;
	//int i= strtol(ffa, nullptr, 16);
	//cout << i;
	//cout << endl; 
	//cout << whynot; 




	return 0; 
	
	
	


	//return 0; 
}
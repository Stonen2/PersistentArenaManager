#include <iostream>
#include <string>
#include <cmath>
#include <bitset>
#include <atomic>
#include <thread>
#include "Arena.h"

using namespace std; 


int main() {
	//superultra<int> a; 
	/*
	a.bitallocate(10);
	a.bitallocate(8);
	a.bitallocate(03);
	a.bitallocate(23);
	a.bitallocate(43);
	a.bitallocate(3);
	a.bitallocate(12);
	a.bitallocate(1);
	a.bitallocate(2);
	a.bitallocate(6);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(10);
	a.bitallocate(8);
	a.bitallocate(03);
	a.bitallocate(23);
	a.bitallocate(43);
	a.bitallocate(3);
	a.bitallocate(12);
	a.bitallocate(1);
	a.bitallocate(2);
	a.bitallocate(6);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(10);
	a.bitallocate(8);
	a.bitallocate(03);
	a.bitallocate(23);
	a.bitallocate(43);
	a.bitallocate(3);
	a.bitallocate(12);
	a.bitallocate(1);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(10);
	a.bitallocate(8);
	a.bitallocate(1);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(1);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(10);
	a.bitallocate(8);
	a.bitallocate(1);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(1);
	a.bitallocate(4);
	a.bitallocate(5);
	a.bitallocate(10);
	a.bitallocate(8);
	a.bitallocate(1);
	a.bitallocate(4);
	a.bitallocate(5);

	//a.bitallocate(10);
	//a.bitallocate(8);
	//a.bitallocate(1);
	//a.bitallocate(4);
	//a.bitallocate(5);
//	a.bitallocate(10);
	//a.bitallocate(4);
	//a.bitallocate(5);
	//a.bitallocate(10);
	//a.bitallocate(5);
	//a.bitallocate(10);

	//a.bitallocate(50);

	
	*/
//	a.allocate();
//	a.allocate();
//	a.allocate();
	//a.allocate();
	//a.allocate();
	//.allocate();
	//a.allocate();
	//a.allocate();

//	a.allocate();
	//a.allocate();
//	cout << endl; 
//	a.print();



	//Arena b(); 

	int b = 1 << 5; 
	cout << b; 
	atomic_uint64_t t = 1; 

	cout << endl;
	if ((t & 1) == 0) {
		cout << "Something";

	}
	cout << endl; 
	cout << t; 


	cout << endl; 
	cout << endl; 
	int number = 256; 
	int cnt = 0; 
	while ((number & 1) == 0)
	{
		cout << number;
		cout << endl; 
		cout << (number & 1);
		cout << endl; 
		cnt++;
		number >>= 1;
	}

	cout << cnt; 

	cout << endl; 
	cout << endl; 
	cout << endl;
	cout << endl;
	void* st = malloc(64);
	Arena a(st, 64);
	
	cout << a.getArenaSize();
	cout << endl; 
	cout << a.getend();
	cout << endl; 
	cout << endl; 
	cout << a.getstart();
	cout << endl; 
	cout << a.getnumbits();
	cout << endl;
	void* testy = a.allocate(4);
	cout << testy << "ITS TESTY";
	cout << endl;
	cout << "WE ALLOCATED";
	cout << endl; 
	cout << endl; 



	//cout << a.map;

	cout << endl; 

}
	
#pragma once 
#include <iostream>
#include "superultra.h"
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std; 
/*s
int main() {
	auto start = std::chrono::high_resolution_clock::now();



	superultra<int> s;
	

	void * t = s.bitallocate(4);
	void* tt = s.bitallocate(4);
	void* ttt = s.bitallocate(4);
	void* tttt  = s.bitallocate(4);
	void* ttttt  = s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);

	
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);


	//5 uints
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	s.bitallocate(8);
	

	//Allocate 20 more ints
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	s.bitallocate(4);
	
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;


	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	//cout << elapsed.count();

	ofstream myfile;
	myfile.open("PersistentResults.txt", std::ios_base::app);
	myfile << "Elapsed Time \n" << elapsed.count() << endl;
	myfile.close();


	return 0; 
}*/
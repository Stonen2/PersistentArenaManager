#pragma once 
#include <iostream>
#include "superultra.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include "implement.h"

using namespace std;

int main() {
	void* te = malloc(1000000);
	auto start = std::chrono::high_resolution_clock::now();


	implement<int> t;
	t.start = te; 

	
	t.bitallocate(64);
	t.bitallocate(64);
	t.bitallocate(64);
	t.bitallocate(64);
	t.bitallocate(64);
	


	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;


	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	//cout << elapsed.count();
	
	ofstream myfile;
	myfile.open("PersistentResults2.txt", std::ios_base::app);
	myfile << "Elapsed Time \n" << elapsed.count() << endl;
	myfile.close();
	

	return 0;
}
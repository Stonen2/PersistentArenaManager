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

	implement<int> t;
	t.allocate();
	t.allocate();
	t.allocate();

	t.start = te;
	auto start = std::chrono::high_resolution_clock::now();
	t.bitallocate(64);
	t.bitallocate(64);
	t.bitallocate(64);
	t.bitallocate(64);
	t.bitallocate(64);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;


	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	cout << endl; 
	
	//cout << elapsed.count();
	


	return 0;
}
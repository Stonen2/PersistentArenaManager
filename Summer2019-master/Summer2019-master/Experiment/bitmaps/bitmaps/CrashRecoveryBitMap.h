#pragma once
#include <iostream>
#include <vector>

using namespace std; 




class CrashRecoveryBitMap {

private: 

	vector<bool> test;

	//Bit Map

public: 

	CrashRecoveryBitMap(size_t s) {

		for (int i = 0; i < s; i++) {
			test.push_back(false);



		}
		//Instantiate Bit map 

	}

	~CrashRecoveryBitMap() {

		//Idk 


	}
	//Take something in and rebuild the bit map
	void recover() {


	}


	//Returns the position in the bit array that is next to be allocated
	int nextfit() {

		for (int i = 0; i < test.size(); i++) {
			if (test[i] == false) {
				return i; 


			}



		}


	}


	//Return the range of positions that are needed and free to allocate the given size too
	int findpos(int pos, size_t s ) {


	}

	//Flip The bit at a given position in the array
	void flipbits(int pos) {

		bool t = test.at(pos);
		if (t == false) {

			t = true; 
			test[pos] = t;

		}
		else {
			t = false; 
			test[pos] = t; 

		}

	}


	//Print all of the contents of the vector
	void print() {

		int count = 0; 
		for (int i = 0; i < test.size(); i++) {

			cout << test.at(i);
			cout << endl; 
			count = i; 

		}
		cout << endl << count;


	}

	/*
		What should this program do? 
		Functions: 

		Recover the Data 

		Namely Build or Rebuild the bit map according the linked list that is taken in 

		Return the Next Fit Position in the array 

		Update the array When the Linked list is updated
		 	
	*/










};
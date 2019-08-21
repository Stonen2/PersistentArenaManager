#pragma once
#include <iostream>
#include <atomic>

using namespace std; 

//What Should an Arena do? 
class Arena {


	using size_type = size_t; 



private: 
	//Each Arena will have the Following
	//A starting Location
	void* start; 
	//The overall Size of the Arena... Usually a Multiple of 64
	size_type ArenaSize; 
	//And Ending Location to Make sure it does not exceed these or to Make sure there is enough room to be allocated
	void* end; 
	//Temporarily Not in use
	int Numbitsalloc; 
	//The number of Bytes that each Bit maps too
	int BytestoBit; 
	//Only need 1 Uint 64 Bit ptr since we are making the number of bytes each bit maps too dynamic
	atomic_uint64_t map;
	
	//int mapsize; 

	//BitMap Here After 
	//atomic<uint64_t> bits[NUMBITS / (8 * sizeof(uint64_t))];




public: 
	

	Arena(void* istart,size_type s) {


		//Set the Starting Location
		start = istart; 
		//Set the Overall Arena Size
		ArenaSize = s; 
		//Set the Ending Location to be the Starting Location + the overall size
		end = &start + s; 
		 
		//All Arenas map to a Dynamic amount of Bits to Bytes. We pass in the size of the Arena then we divide it by 64 or the number of bits in the pointer

		int N= numbyte(s); 
		
		BytestoBit = 1 << N;
		BytestoBit = N;
		map = 1; 
		Numbitsalloc = 0; 
	}

	int numbyte(size_type s) {
		int coin = -1; 
		int t = s; 
	
		t = s / 64;
		

		while (s > 1) {

			s = s / 64; 
			coin++; 
		



		}

		return t;
	}




	size_type getArenaSize() { return ArenaSize; }
	void* getstart() { return start;  }
	void* getend() { return end;  }
	void setArenaSize(size_type t) { ArenaSize = t; }
	void setStart(void* s) { start = s;  }
	void setend() { end = &start + ArenaSize; }
	int getnumbits() { return BytestoBit; }
	//atomic_uint64_t getmap() { return map; }

	//Magic
	void*  allocate(size_type s) {	
		int bits = decrypt(s);
		 

		
		int nu = 0; 
		int nup = 0; 
		int temp = Numbitsalloc;
		bool got = false;
		if (((map << bits) & 1) == 0) {
			got = true;
			Numbitsalloc += bits; 
			if (Numbitsalloc > 64) {
				Numbitsalloc = temp; 
				return NULL; 
			}
			for (int i = 0; i < bits; i++) {
				map = map << 1;
			}
			void* temp = &start + (BytestoBit * ( Numbitsalloc));
			return temp;
		}
		if (got == false) {
			return NULL;
		}
	}


	int decrypt(size_type s) {
		
		//float ss= s / BytestoBit;
		int t =ceil( s / BytestoBit);
		if (t < 1) {
			return 1; 
		}

		return t;
	}

	//No Magic 

	void free() {
		map = 0; 
	}

};







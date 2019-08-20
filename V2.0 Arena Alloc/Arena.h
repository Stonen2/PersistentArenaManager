#pragma once
#include <iostream>
#include <atomic>

using namespace std; 

//What Should an Arena do? 
class Arena {


	using size_type = size_t; 



private: 
	//Each Arena will have the Following

	void* start; 
	size_type ArenaSize; 
	void* end; 
	int Numbits; 
	int BytestoBit; 
	atomic_uint64_t map;
	
	//int mapsize; 

	//BitMap Here After 
	//atomic<uint64_t> bits[NUMBITS / (8 * sizeof(uint64_t))];




public: 
	

	Arena(void* istart,size_type s) {


		start = istart; 
		ArenaSize = s; 
		end = &start + s; 
		 
		//All Arenas map 1 bit to 32 Bytes
		int N= numbyte(s); 
		
		BytestoBit = 1 << N;
		BytestoBit = N;
		map = 1; 
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
		 

		int cnt = 0;
	
		//Now We look at all 0s
		int pos = cnt; 
		int nu = 0; 
		int nup = 0; 
		bool got = false;
		if (map == 0) {
			got = true;
			for (int i = 0; i < nu; i++) {
				map = map >> 1;
			}
			void* temp = &start + (BytestoBit * (pos + nup));
			
			return temp;
		}
		while ((map & 1) == 1){
		
			nu++;
			map = map >> 1; 


			if (nu == bits) {
				nup = nu; 
				got = true; 
				for (int i = 0; i < nu; i++) {
					map = map << 1; 
				}
				void* temp = &start + (BytestoBit * (pos + nup));
				
				return temp;

			}

			

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







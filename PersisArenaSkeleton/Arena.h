#pragma once
#include <iostream>
#include<atomic>



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


	//BitMap Here After 
	//atomic<uint64_t> bits[NUMBITS / (8 * sizeof(uint64_t))];




public: 

	Arena(void* istart,size_type s,int iNumbits ) {


		start = istart; 
		ArenaSize = s; 
		end = &start + s; 
		Numbits = iNumbits; 
		//All Arenas map 1 bit to 32 Bytes
		BytestoBit = 32; 

	}



	size_type getArenaSize() { return ArenaSize; }
	void* getstart() { return start;  }
	void* getend() { return end;  }
	void setArenaSize(size_type t) { ArenaSize = t; }
	void setStart(void* s) { start = s;  }
	void setend() { end = &start + ArenaSize; }
	





};







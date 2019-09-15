#pragma once
#include <atomic>
#include <sys/mman.h>

using namespace std; 


class Persist {

private:

	void* start;
	size_t totalsize;
	size_t nexts; 

	//Purely going to be for Testing Purposes
	int numallocs
	///Array 1
	atomic<uint64_t> bits[2030 / (8 * sizeof(uint64_t))];
	
	///Array 2
	atomic<uint64_t>transactions[2 * (2030/(8 * sizeof(uint64_t)))]


	void* mymmap() {
		void* region = ::mmap(nullptr,
			totalsize,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			-1,
			0);

		if (region == NULL) {
			return NULL;
		}
		return region;


	}

	void mymunmap() {
		munmap(start, totalsize);

	}
	

	size_t PAD(size_t s) {
		size_t temp = s;
		if (s % 8 == 0) {
			return temp;

		}
		else {
			temp = s / 8;
			size_t offset = 8 - temp;
			temp = s + offset;
			return temp;

		}

		//return temp; 
	}

	void* malloc(size_t s) {

		size_t pad_size = PAD(s);
		void *  retval = &start + nexts;
		nexts += pad_size;
		
		return retval;


	}


	int numheaplets(size_t s) {
		int temp = (s / 64);
		return temp; 


	}



public: 

	void init(int i) {
		if (i == 1) {
			totalsize = 65000;
		}
		else if (i == 2) {
			totalsize = 130000; 
		}
		else {
			totalsize = 130000; 
		}
		start = mymmap();
		//Start will be the offset of the Size of the Data Structures. 
		start = 0; 


	}
	void destroy() {
		mymunmap();
	}


	void* allocate(size_t st) {
		int temp = numheaplets(st);
		//Call A function to traverse find and move atomically all the number of heaplets needed. 

		void * region to alloc = malloc(temp * 32);

		return region; 
	}

	void free() {
		



	}


};



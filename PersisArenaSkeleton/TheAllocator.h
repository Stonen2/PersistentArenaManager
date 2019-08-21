#pragma once
#include <atomic>

#include "Arena.h"

//What should the allocator do? 





//We have 4 API calls

//Obviously the Allocator will need Free Lists and Traversing Free List
//Should look something like Looping through a Linked Listg or Vector then doing a .HasRoom(Size) 
//Then Next or then Manipulating that Arena 
//Pad() --> Returns the next 64 Size Maybe Look into reworking
//There should be a series of Pad functions 
// 

//Take in a given Size Then we send that to the Pad where we round it up to the Next Size Class
//Size Classes to start will be In Terms of size 32 Bytes 
//Thus we are allocating 32 Byte Blocks to every allocation 
//
//Once the size is Determined we then Find the First size Greater than the Size of the Block So if It is size 32 then we traverse the 64 Block Free List
//Simple Alogirthm to determine and find the 

//Malloc Then Takes in a Size 
//Malloc then Calls Find List. 
// Traverses the List 
//So The overall program will need a Void * Start location 
//A Size_T of the overall Size of the program
//It will need a Series of Lists 
//Malloc Function 
//


/// - init(void* base, size_t offset): init() receives a previously mmap'd region of memory
///   and its maximum size.  It finds the allocator within that region, initializes this
///   PersistentArenaManager from that allocator, and prepares to serve future allocation
///   and free requests.


/// - destroy(): currently a no-op, but part of the API in case we ever decide that init()
///   should be responsible for calling mmap... in that case, destroy() would call munmap()


/// - get_mem(size_t): rounds the given size up to the next size class, finds (or creates)
///   an arena that has a free block of that size, and reserves / returns that block

///return_mem(void*) : Determines the arena from which the provided pointer was allocated,
///   and returns that pointer to the arena.

//If the Void * is in between the range of the starting Void * in a given arena and the ending void * then we have the arena and then return
//The pointer to the given Arena --> Dont know how this is useful but ok 

using size_type = size_t; 






class TheAllocator {
private: 

	void* start;
	size_type TotalSize; 
	void* end; 



	void* malloc(size_type t) {



	}
	size_type pad(size_type t) {
		if (t < 64) {
			return 64; 
		}
		else if (t < 128) {
			return 128; 
		}
		else if (t < 256) {
			return 256; 
		}
		else if (t < 512) {
			return 512; 
		}
		else if (t < 1024) {
			return 1024;
		}
		else if (t < 2048) {
			return 2048; 
		}
		else if (t < 4096) {
			return 4096;
		}
		else {

			return t * 2; 
		}


	}

public: 




	void init(void* base, size_type offset) {
		start = base;
		TotalSize = offset;
		end = &base + offset;

	}
	void* getmem(size_type s) {
		size_type findring = pad(s);
		if (findring == 64) {
			//ALgorithm for 64
		}
		else if (findring == 128) {

		}
		else if (findring == 256) {

		}
		else if (findring == 512) {

		}
		else if (findring == 1024) {


		}
		else if (findring == 2048) {

		}
		else if (findring == 4096) {

		}
		else {


		}


	}



	void destroy() {
		//No -Op
	}






};
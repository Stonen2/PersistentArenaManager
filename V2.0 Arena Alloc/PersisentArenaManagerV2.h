#pragma once

#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <atomic>
#include <cstdint>
using namespace std;



/// [nas] Rename from superultra to PersistentArenaManager
///
/// The PersistentArenaManager is a programmer-visible object that provides the ability to
/// carve out regions from a mmap'd file and use them as if they were the return value from
/// calls to malloc().  PersistentArenaManager also supports free().
///
/// The api consists of four functions:
/// - init(void* base, size_t offset): init() receives a previously mmap'd region of memory 
///   and its maximum size.  It finds the allocator within that region, initializes this 
///   PersistentArenaManager from that allocator, and prepares to serve future allocation
///   and free requests.
/// - destroy(): currently a no-op, but part of the API in case we ever decide that init() 
///   should be responsible for calling mmap... in that case, destroy() would call munmap()
/// - get_mem(size_t): rounds the given size up to the next size class, finds (or creates)
///   an arena that has a free block of that size, and reserves / returns that block
/// - return_mem(void*): Determines the arena from which the provided pointer was allocated,
///   and returns that pointer to the arena.
class BaseArena {
	// this would have common fields of arenas, such as size?
	///The total number of bits in the Arena
	int numbits;
	///Every Arena will have a size that it has been allocated to, We CANNOT exceed this chunk
	size_t chunksize;
	///EVery Arena will have a starting point or the amount of room that it can allocate
	void* startar;
	///The total number of bits that are remainning... NOT IN ONE CONTINUATION!
	int numleft;
	void* endpos; 

	///We want to set the total number of bits for a given base arena
	void setnumbits(int innumbits) {
		numbits = innumbits;
	}
	///We want to set the size of the overall arena
	void setchunk(size_t inchunksize) {
		chunksize = inchunksize;
	}
	///We want to set the starting location of the arena 
	void setstar(void* instartar) {
		startar = instartar;
	}
	///We want to set the remainning number of bits
	void setnumleft(int innumleft) {
		numleft = innumleft;
	}
	void setendst(void * inendstar) {
		endpos = inendstar; 
	}
	void* getendpos() {
		return endpos; 
	}

	///This will return the number of bits remainning to be allocated
	int getnumleft() {
		return numleft;
	}
	///This will return the overall size of the bits in the arena
	int getbit() {
		return numbits;
	}
	///This will return the overall size of the arena
	size_t getchunk() {
		return chunksize;
	}
	///This will return the start location of a given arena 
	void* getstar() {
		return startar;
	}



};

template<int NUMBITS, int CHUNKSIZE>
class Arena : public BaseArena {
	// this would have the bitmap, and the logic for atomically setting/clearing bits
	atomic<uint64_t> bits[NUMBITS / (8 * sizeof(uint64_t))];
	char* chunks[NUMBITS * CHUNKSIZE];
	Arena* next;
	int totalsizechu = NUMBITS * CHUNKSIZE;
	int totalsizeui = (NUMBITS / (8 * sizeof(uint64_t)));
	int numchunkperbit = NUMBITS / (8 * sizeof(uint64_t));

public:
	///On creation we want to take in a void * that will be given to us by the malloc returned in the parent program IE Persistent Arena Manager
	///Then we want to set the Base Arena Meta data that we know from the start of the creation
	///This is known because the template allows us to know the number of bits that will be available as well as the size of the chunk that has just been allocated
	///

	Arena(void* instart) {

		BaseArena::setchunk(CHUNKSIZE);
		BaseArena::setstar(instart);
		BaseArena::setnumbits(NUMBITS);
		BaseArena::setnumleft(NUMBITS);
		BaseArena::setendst((&instart + chunksize));
	}

	void* getend() {

		return BaseArena::getendpos;
	}
	void* getstar() {

		return BaseArena::getstar;
	}

	///See if there is room in the bit map that can be allocated'
	///This will loop through the overall char * chunks knowing that each position corresponds to 1 byte
	///We then find the sequential number of bytes that we need to allocate then we return if that number of bytes is able to be allocated
	/// Or false that we do not have enough rooom in chunk 
	bool checkroomchunks(size_t s) {
		size_t counter = 0;

		for (int i = 0; i < totalsize; i++) {
			for (int j = i; j < totalsize; j++) {
				if (counter == s) {
					return true;
				}
				if (chunks[j] == 0) {
					counter = counter + 1;
				}
				else {
					counter = 0;
					break;
				}
			}
		}
		return false;
	}
	///Take in a size and a number in the array pointer then we check i
	bool checkroombits(size_t s) {
		size_t counter = 0;
		for (int i = 0; i < totalsizeui; i++) {
			for (int j = 0; j < 63; j++) {

				if (counter == s) {
					return true;

				}
				if (bits[i] >> j && 1 == 0) {
					counter = counter + 1;


				}
				else {
					counter = 0;

				}


			}

		}
		return false;

	}

	///Change the values in the bitmap to reflect that the proper memory has been allocated
	void allocateptr(size_t s, size_t pos, int startcha, int endcha)
	{


		size_t temp = pos + s;

		//Fill the first pointer
		for (int j = startcha; j < endcha; j++) {



			//fill the rest
			for (size_t i = pos; i < temp; i++) {
				bits[j] &= 1 << i;


			}
		}

	}

	void allocatechu(size_t s, size_t pos) {
		size_t temp = s = pos;
		for (size_t i = pos; i < temp; i++) {
			chunks[i] = 1;



		}


	}

	///Give the Persistent Arena Manager the Position of the array that can allocate a number of blocks IE if there is size 5 left Allocate Size 5
	size_t poschunk(size_t s) {
		size_t counter = 0;

		for (int i = 0; i < totalsize; i++) {
			for (int j = i; j < totalsize; j++) {
				if (counter == s) {

					allocatechu(s, counter);
					return counter;
				}
				if (chunks[j] == 0) {
					counter = counter + 1;
				}
				else {
					counter = 0;
					break;
				}
			}
		}


		//Loop through the list
		//Find the number of bits 
		//Return its position to the Persistent Arena Manager
		//Change the Bit map 


	}

	size_t posptr(size_t s, int ptrar) {
		size_t counter = 0;
		int startcha = 0;
		int endcha = startcha;
		bool continues = false;
		for (int i = 0; i < totalsizeui; i++) {
			if (continues == true) {
				endcha = i;
				continues = false;
			}
			else {
				startcha = i;


			}


			for (int j = 0; j < 63; j++) {

				if (counter == s) {

					endcha = i;
					allocateptr(s, counter, startcha, endcha);
					return counter;

				}
				if (bits[i] >> j && 1 == 0) {
					counter = counter + 1;
					if (j == 63) {
						continues = true;

					}

				}
				else {
					counter = 0;
					continues = false;

				}


			}

		}


	}



};

template <class s,class ps> class linked {

	Arena<s,ps>* head;
	Arena<s,ps>* temp;
	

	///The following is a series of functions that will be used for the linked list structure to hold arenas
	Arena<s,ps>* tail;
	
	bool isEmpty()
	{
		return head == NULL;
	}


	void insert(Arena<s, ps> a)
	{
		temp = a;
		//temp->data = x;
		if (isEmpty())
		{
			temp->next = NULL;
			tail = temp;
		}
		else
			temp->next = head;
		head = temp;
	}

	void insertAtEnd(Arena<s, ps> x)
	{
		temp = x;
		//temp->data = x;
		temp->next = NULL;
		if (isEmpty())
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}

	void remove(Arena<s, ps> x)
	{
		temp = head;
		Arena* prev;
		while (temp->next != NULL && temp->data != x)
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp->data == x)
		{
			prev->next = temp->next;
			delete temp;
		}
		else if (temp->next == NULL)
		{
			cout << "Error: Number Not found..." << endl;
		}
	}

	Arena<s,ps>*  find(void * s)
	{
		int i;
		temp = head; 
		while (temp != NULL) {

			if (&temp.getstart() >= &s && &s < &temp->getend()) {
				return temp; 
			}

			else {
			temp = temp->next; 
			}

		}
		return NULL; 
	}

	void display()
	{
		if (!isEmpty())
		{
			for (temp = head; temp != NULL; temp = temp->next)
				cout << temp->data << " ";
			cout << endl;
		}
		else
		{
			cout << "List is Empty!" << endl;
		}
	}


};




template<class T> class PersistentArenaManager {
	using value_type = T;
	using pointer = T *;
	using const_pointer = const T*;
	//These variables will be used for allocating the memory IE void * commonly used
	using size_type = size_t;
	using void_star = void*;


protected:




private:
	///The base or the start of the MMAP file 
	void_star base;
	/// Pointer to the end of the MMAP file
	void_star endregion;
	/// End of the region passed by init
	size_type regionOffset;
	///The offset to the next part of te region that is ready to be allocated
	size_type NextFree;
	//
	

	void mmap() {

		//No op 
	}

	void munmap() {

		//No Op
	}

	void_star malloc(size_type s) {
		void_star test = NextFree + s; 
		NextFree += s; 
		if (&test > &endregion) {
			cout << "No More room to allocate";
			return NULL;
		}
		else {
			return test; 

		}

	}

	//Round to the nearest 64th 
	size_type pad(size_type s) {
		size_type temporary = s;
		if (s < 64) {
			return 64; 

		}
		else if (s < 128) {
			return 128;
		}
		else if (s < 256) {
			return 256;
		}
		else if (s < 512) {
			return 512;
		}
		else if (s < 1024) {
			return 1024;
		}
		else if (s < 2048) {
			return 2048;
		}
		else if (s < 4096) {
			return 4096;
		}
		else {
			cout << "Too Large to Allocate";

		}


		return temporary;
	}


	//This functions goal is to be used to manipulate a void pointer to then be returned to the programmer 
	//The function will take in the size_t of the position and then it will take the size of the object that needs
	//to be allocated then it will take in the start of the arena that the object is being allocated too
	//Then a new void pointer will be created and returned that will be pointing to an object within the 
	//Range of bits in the given arena
	void_star lowlevelalloc(size_type posstart, size_type thisbig, void_star arenast) {
		//Make a new void * pointer that will point to the arena start + the positition of the next free spot in the bit map 
		// + the overall size that needs to be allocated. 
		void_star newplace = &arenast + posstart + thisbig;
		//Return new value 
		return newplace;

	}

	///Stop Linked List
public:


	/// [nas] Rename from superultra to PersistentArenaManager
///
/// The PersistentArenaManager is a programmer-visible object that provides the ability to
/// carve out regions from a mmap'd file and use them as if they were the return value from
/// calls to malloc().  PersistentArenaManager also supports free().
///
/// The api consists of four functions:





	/// - init(void* base, size_t offset): init() receives a previously mmap'd region of memory 
///   and its maximum size.  It finds the allocator within that region, initializes this 
///   PersistentArenaManager from that allocator, and prepares to serve future allocation
///   and free requests.
	void init(void_star inbase, size_type inoffset) {
		//To start
		linked<64, 64> s = new linked<64,64>();
		linked<64, 128> s1 = new linked<64, 128>();
		linked<64, 256> s2 = new linked<64, 256>();
		linked<64, 512> s3 = new linked<64, 512>();
		linked<64, 1024> s4 = new linked<64, 1024>();
		linked<64, 2048> s5 = new linked<64, 2048>();
		linked<64, 4096> s6 = new linked<64, 4096>();


		//4096
		Arena<64, 64> le = new Arena<64, 64>(inbase);
		s.insert(le);
		base = inbase;
		endregion = &inbase + inoffset;

	}
	/// - destroy(): currently a no-op, but part of the API in case we ever decide that init() 
///   should be responsible for calling mmap... in that case, destroy() would call munmap()
	void destroy() {
		//No-Op
	}



	/// - get_mem(size_t): rounds the given size up to the next size class, finds (or creates)
	///   an arena that has a free block of that size, and reserves / returns that block
	void_star get_mem(size_type size) {
		size_type t = pad(size);
		void* test = malloc(size);
		bool alloc = true; 

		if (t == 64) {
			while (alloc == false) {
				if (s.head == NULL) {
					Arena<64, 64> le = new Arena<64, 64>(test);
					s.insert(le);
				}
				else if (alloc == false) {
					Arena<64, 64> le = new Arena<64, 64>(test);
					s.insert(le);

				}
				else {
					//Try Allocating
					Arena<64,64>* temp = s.head;
					while (temp != NULL) {
						
						//void_star store = hub(temp, needbig);
						if (temp->checkroombits == true && temp->checkroomchunks == true) {
							temp->allocatechu;
							temp->allocateptr;
							size_type st = temp->poschunk;
							void_star store = lowlevelalloc(size, st, test);
							if (store > temp->getend()) {
								//Need More Memory 
								//alloc == false; 
								
							}
							else {
								return store; 
							} 
						}
						else {
							//Need More memory, Allocate some more 
							//alloc = false; 
							temp = temp->next; 
						}
					}
					alloc = false; 
				}
			}

		}
		else if (t == 128) {

			while (alloc == false) {
				if (s1.head == NULL) {
					Arena<64, 128> le = new Arena<64, 128>(test);
					s1.insert(le);
				}
				else if (alloc == false) {
					Arena<64, 128> le = new Arena<64, 128>(test);
					s1.insert(le);

				}
				else {
					//Try Allocating
					Arena<64, 128> * temp = s1.head;
					while (temp != NULL) {

						//void_star store = hub(temp, needbig);
						if (temp->checkroombits == true && temp->checkroomchunks == true) {
							temp->allocatechu;
							temp->allocateptr;
							size_type st = temp->poschunk;
							void_star store = lowlevelalloc(size, st, test);
							if (store > temp->getend()) {
								//Need More Memory 
								//alloc == false;
							}
							else {
								return store;
							}
						}
						else {
							//Need More memory, Allocate some more 
							//alloc = false;
							temp = temp->next; 
						}
					}
					alloc = false; 

				}
			}



		}
		else if (t == 256) {
			while (alloc == false) {
				if (s2.head == NULL) {
					Arena<64, 256> le = new Arena<64, 256>(test);
					s2.insert(le);
				}
				else if (alloc == false) {
					Arena<64, 256> le = new Arena<64, 256>(test);
					s2.insert(le);

				}
				else {
					//Try Allocating
					Arena<64, 256> * temp = s2.head;
					while (temp != NULL) {

						//void_star store = hub(temp, needbig);
						if (temp->checkroombits == true && temp->checkroomchunks == true) {
							temp->allocatechu;
							temp->allocateptr;
							size_type st = temp->poschunk;
							void_star store = lowlevelalloc(size, st, test);
							if (store > temp->getend()) {
								//Need More Memory 
								//alloc == false;
							}
							else {
								return store;
							}
						}
						else {
							//Need More memory, Allocate some more 
							//alloc = false;
							temp = temp->next;
						}
					}
					alloc = false;

				}
			}

		}
		else if (t == 512) {
		while (alloc == false) {
			if (s3.head == NULL) {
				Arena<64, 512> le = new Arena<64, 512>(test);
				s3.insert(le);
			}
			else if (alloc == false) {
				Arena<64, 512> le = new Arena<64, 512>(test);
				s3.insert(le);

			}
			else {
				//Try Allocating
				Arena<64, 512> * temp = s3.head;
				while (temp != NULL) {

					//void_star store = hub(temp, needbig);
					if (temp->checkroombits == true && temp->checkroomchunks == true) {
						temp->allocatechu;
						temp->allocateptr;
						size_type st = temp->poschunk;
						void_star store = lowlevelalloc(size, st, test);
						if (store > temp->getend()) {
							//Need More Memory 
							//alloc == false;
						}
						else {
							return store;
						}
					}
					else {
						//Need More memory, Allocate some more 
						//alloc = false;
						temp = temp->next;
					}
				}
				alloc = false;

			}
		}

		}
		else if (t == 1024) {
		while (alloc == false) {
			if (s4.head == NULL) {
				Arena<64, 1024> le = new Arena<64, 1024>(test);
				s4.insert(le);
			}
			else if (alloc == false) {
				Arena<64, 1024> le = new Arena<64, 1024>(test);
				s4.insert(le);

			}
			else {
				//Try Allocating
				Arena<64, 1024> * temp = s4.head;
				while (temp != NULL) {

					//void_star store = hub(temp, needbig);
					if (temp->checkroombits == true && temp->checkroomchunks == true) {
						temp->allocatechu;
						temp->allocateptr;
						size_type st = temp->poschunk;
						void_star store = lowlevelalloc(size, st, test);
						if (store > temp->getend()) {
							//Need More Memory 
							//alloc == false;
						}
						else {
							return store;
						}
					}
					else {
						//Need More memory, Allocate some more 
						//alloc = false;
						temp = temp->next;
					}
				}
				alloc = false;

			}
		}

		}
		else if (t == 2048) {
		while (alloc == false) {
			if (s5.head == NULL) {
				Arena<64, 2048> le = new Arena<64, 2048>(test);
				s5.insert(le);
			}
			else if (alloc == false) {
				Arena<64, 2048> le = new Arena<64, 2048>(test);
				s5.insert(le);

			}
			else {
				//Try Allocating
				Arena<64, 2048> * temp = s5.head;
				while (temp != NULL) {

					//void_star store = hub(temp, needbig);
					if (temp->checkroombits == true && temp->checkroomchunks == true) {
						temp->allocatechu;
						temp->allocateptr;
						size_type st = temp->poschunk;
						void_star store = lowlevelalloc(size, st, test);
						if (store > temp->getend()) {
							//Need More Memory 
							//alloc == false;
						}
						else {
							return store;
						}
					}
					else {
						//Need More memory, Allocate some more 
						//alloc = false;
						temp = temp->next;
					}
				}
				alloc = false;

			}
		}

		}
		else if (t == 4096) {
			while (alloc == false) {
				if (s1.head == NULL) {
					Arena<64, 4096> le = new Arena<64, 4096>(test);
					s6.insert(le);
				}
				else if (alloc == false) {
					Arena<64, 4096> le = new Arena<64, 4096>(test);
					s6.insert(le);

				}
				else {
					//Try Allocating
					Arena<64, 4096> * temp = s6.head;
					while (temp != NULL) {

						//void_star store = hub(temp, needbig);
						if (temp->checkroombits == true && temp->checkroomchunks == true) {
							temp->allocatechu;
							temp->allocateptr;
							size_type st = temp->poschunk;
							void_star store = lowlevelalloc(size, st, test);
							if (store > temp->getend()) {
								//Need More Memory 
								//alloc == false;
							}
							else {
								return store;
							}
						}
						else {
							//Need More memory, Allocate some more 
							//alloc = false;
							temp = temp->next;
						}
					}
					alloc = false;

				}
		}

		}
		else {
			cout << "No Op";

		}

	}



	/// - return_mem(void*): Determines the arena from which the provided pointer was allocated,
///   and returns that pointer to the arena.
	void_star return_mem(void_star findarena) {
		//Search 64
		//Search 128 
		//Etc...
	//Write a function if this void star
		if (s.find(findarena) == true) {
			void_star t = s.find(findarena);
			return t; 

		}
		else if (s1.find(findarena) == true) {
			void_star t = s1.find(findarena);
			return t;

		}
		else if (s2.find(findarena) == true) {
			void_star t = s2.find(findarena);
			return t;

		}
		else if (s3.find(findarena) == true) {
			void_star t = s3.find(findarena);
			return t;

		}
		else if (s4.find(findarena) == true) {
			void_star t = s4.find(findarena);
			return t;

		}
		else if (s5.find(findarena) == true) {
			void_star t = s5.find(findarena);
			return t;

		}
		else if (s6.find(findarena) == true) {
			void_star t = s6.find(findarena);
			return t;

		}
		else {
			return NULL; 
		}
		
		
		
		/*
	if findarena > arena.startbase && findarena < arena.endbase{
	return arena 
	else next arena 
	*/


	}

};
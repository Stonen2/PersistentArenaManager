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

template<int NUMBITS,int CHUNKSIZE>
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
	
	Arena(void * instart) {

		BaseArena::setchunk(CHUNKSIZE);
		BaseArena::setstar(instart);
		BaseArena::setnumbits(NUMBITS);
		BaseArena::setnumleft(NUMBITS);
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
	void allocateptr(size_t s, size_t pos,int startcha, int endcha) 
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
	Arena* head; 
	Arena* temp; 


	///The following is a series of functions that will be used for the linked list structure to hold arenas
	Arena* tail;
	bool isEmpty()
	{
		return head == NULL;
	}


	void insert(Arena a)
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

	void insertAtEnd(Arena x)
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

	void remove(Arena x)
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

	void find(Arena x)
	{
		int i;
		for (i = 1, temp = head; temp->next != NULL && temp->data != x; temp = temp->next, i++);
		if (temp->data == x)
		{
			cout << "Found at position:" << i << endl;
		}
		else if (temp->next == NULL)
		{
			cout << "Error: Number Not found..." << endl;
		}
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

	void mmap() {

		//No op 
	}

	void munmap() {

		//No Op
	}

	//Round to the nearest 64th 
	size_type pad(size_type s) {
		size_type temporary = s; 


		return temporary; 
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
		Arena<64,64> s = new Arena<64, 64>(inbase);
		insert(s);
		base = inbase; 
		endregion = inoffset; 

	}
	/// - destroy(): currently a no-op, but part of the API in case we ever decide that init() 
///   should be responsible for calling mmap... in that case, destroy() would call munmap()
	void destroy() {
		//No-Op
	}



	/// - get_mem(size_t): rounds the given size up to the next size class, finds (or creates)
	///   an arena that has a free block of that size, and reserves / returns that block
	void_star get_mem(size_type size) {
		//List is empty 
		if (head == NULL) {
			//Create a New Arena}


	}



	/// - return_mem(void*): Determines the arena from which the provided pointer was allocated,
///   and returns that pointer to the arena.
	void_star return_mem(void_star findarena) {


	}









};
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

public:
	///On creation we want to take in a void * that will be given to us by the malloc returned in the parent program IE Persistent Arena Manager
	///Then we want to set the Base Arena Meta data that we know from the start of the creation
	///This is known because the template allows us to know the number of bits that will be available as well as the size of the chunk that has just been allocated
	Arena(void * instart) {

		BaseArena::setchunk(CHUNKSIZE);
		BaseArena::setstar(instart);
		BaseArena::setnumbits(NUMBITS);
		BaseArena::setnumleft(NUMBITS);
	}



	///See if there is room in the bit map that can be allocated
	bool checkroom(size_t s) {
		//for(int i = 0; i < chunks)
	}

	///Change the values in the bitmap to reflect that the proper memory has been allocated
	void allocate() {

	}

	///Give the Persistent Arena Manager the Position of the array that can allocate a number of blocks IE if there is size 5 left Allocate Size 5
	size_t pos(size_t s) {
		//Loop through the list
		//Find the number of bits 
		//Return its position to the Persistent Arena Manager
		//Change the Bit map 


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

	///Stop Linked List
public: 

	void init(void_star base, size_type offset) {

	}

	void destroy() {
		//No-Op
	}

	void_star get_mem(size_type size) {

	}

	void_star return_mem(void_star findarena) {


	}




	void_star malloc(size_type s) {

	}






};
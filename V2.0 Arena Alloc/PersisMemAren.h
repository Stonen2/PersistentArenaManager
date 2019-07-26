#pragma once 
#include <sys/mman.h>
#include <iostream>

using namespace std; 



class arena {
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
	char* chunks;
	int *bits;
	
	//int chunksize; 



public:
arena* next;
	arena() {

	}
	~arena() {

	}

	int getnumbits() {return numbits; }

	size_t getchunksize() {return chunksize;}

	void* getstar() {return startar;}

	int getnumleft() {return numleft;}

	void* getendpos() {return endpos;}

	void setnumbits(int innum) {numbits = innum;}

	void setchunksize(size_t inchun) { chunksize = inchun; bits = new int[chunksize]; for (int i = 0; i < chunksize; i++) { bits[i] = 0; } }

	void setstar(void * inst) { startar = inst;}

	void setnumleft(int inum) {numleft = inum;}

	void setendpos(void* inen) {endpos = inen;}
	///See if there is room in the bit map that can be allocated'
///This will loop through the overall char * chunks knowing that each position corresponds to 1 byte
///We then find the sequential number of bytes that we need to allocate then we return if that number of bytes is able to be allocated
/// Or false that we do not have enough rooom in chunk 
	bool checkroomchunks(size_t s) {
		size_t counter = 0;
		for (int i = 0; i < chunksize; i++) {

			for (int j = 0; j < chunksize; j++) {
				if (counter == s) {
					return true; 
				}
				if (bits[j] == 0) {
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

	void flipbit(size_t start, size_t size) {
		int temp = (int) start; 

		for (int i = start; i < size; i++) {
			bits[i] = 1;


		}
	}


	size_t getpos(size_t s) {
		size_t counter = 0; 
		size_t pos = 0; 
		for(int i = 0; i < chunksize; i++){
			counter = 0; 
			pos = i;
			for (int j = 0; j < chunksize; j++) {
				if (counter == s) {
					flipbit(pos, s);
					return pos; 
				}
				if (bits[j] == 0) {
					counter = counter + 1; 
				}
				else {
					counter = 0; 
					break; 
				}

			}
		}
		return -1; 

	}
};



class PersisMemAren {
private:
	///The base or the start of the MMAP file 
	void* base;
	/// Pointer to the end of the MMAP file
	void* endregion;
	/// End of the region passed by init
	size_t regionOffset;
	///The offset to the next part of te region that is ready to be allocated
	size_t NextFree;
	///64 bytes
	arena* head; 
	///128 bytes
	arena* head1;
	///256 bytes
	arena* head2;
	///512 bytes
	arena* head3;
	///1024 bytes
	arena* head4;
	///2048 bytes
	arena* head5; 
	///4096 bytes
	arena* head6;
	///Greater than 4096
	arena* head7; 


	//Linked List
	//Malloc
	//Getmem
	// Return mem
	//Destroy -> No Op 
	//INit

	///Allocate room to make a new arena
	void * malloc(size_t s) {
		size_t tg = pad(s);
		void*  test = &NextFree + tg;
		NextFree += tg;
		if (&test > & endregion) {
			cout << "No More room to allocate";
			return NULL;
		}
		else {
			return test;

		}

	}

	///Allocate from an arena 
	void* arenamalloc(arena e, size_t s) {
		void* test = e.getstar();
		if (e.checkroomchunks(s) == false) {
			cout << "No Room to allocate";
			return NULL; 
			
		}
		else {
			size_t pos = e.getpos(s);
			test = &test + s + pos;
			if (test > e.getendpos()) {
				cout << "Not enough room";
			}
			else {
				return test;
			}
		}
		

	}

	//Round to the nearest 64th 
	size_t pad(size_t s) {
		size_t temporary = s;
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
			return temporary;

		}
	}
	///Set all of the data in an arena 
	arena* arenainfo(arena* e,size_t chunk) {


		e->setchunksize(chunk);
		e->setendpos(&e + chunk);
		e->setnumbits(chunk);
		e->setstar(e);


	}

	void* maps(size_t f) {
		void* temp;
		temp = mmap(nullptr,
			f,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			-1,
			0);
		return temp;

	}

	void munmap() {


	}

	

	void addtolist(size_t a) {
		size_t s = pad(a);


		///Start the chain
		if (a == 64) {
			if (head == NULL) {
				arena* e; 
				e = reinterpret_cast<arena*>(malloc(a));
				e = arenainfo(e);
				head = e; 
				head->next = NULL; 

			}
			else if (head->next == NULL) {


				arena* te;
				//Allocate this new temp to be the malloc 
				te = reinterpret_cast<arena*>(malloc(a));
				//te->startarena = te; 
				//Set Arena values
				te = arenainfo(te,s);
				//Place it in the list 
				head->next = te;
			}
			else {
				arena* he;
				arena* Next_Arena;
				Next_Arena = head;
				while (Next_Arena->next != NULL) {
					//Get to the last Node
					Next_Arena = Next_Arena->next;
				}
				//Once at end of list insert new node into list
				he = reinterpret_cast<arena*>(malloc(a));
				//Set values of the new arena
				he = arenainfo(he);
				//Make sure it is in the list 
				Next_Arena->next = he;


			}
		}


		if (Head_Arena == NULL) {
			Arena* e;
			e = reinterpret_cast<Arena*>(malloc());

			//Set all of Node values in e; 
			//SEt head Node to E; 
			e = arenainfo(e);
			//SEt Tail Not to HeadNode -> next
			Head_Arena = e;
			Head_Arena->next = NULL;
			start = Head_Arena;
			/*
			Call Functions to Establish Node
			*/
			//Head Node Now E
			Next_Arena = Head_Arena->next;
		}
		else if (Head_Arena->next == NULL) {
			//Temp Arena 

			Arena* te;
			//Allocate this new temp to be the malloc 
			te = reinterpret_cast<Arena*>(malloc());
			//te->startarena = te; 
			//Set Arena values
			te = arenainfo(te);
			//Place it in the list 
			Head_Arena->next = te;

		}
		else {
			//Arena* temp; 
			Arena* he;
			Next_Arena = Head_Arena;
			while (Next_Arena->next != NULL) {
				//Get to the last Node
				Next_Arena = Next_Arena->next;
			}
			//Once at end of list insert new node into list
			he = reinterpret_cast<Arena*>(malloc());
			//Set values of the new arena
			he = arenainfo(he);
			//Make sure it is in the list 
			Next_Arena->next = he;
		}
		//Function DOne
	}


public:

	/// - init(void* base, size_t offset): init() receives a previously mmap'd region of memory 
///   and its maximum size.  It finds the allocator within that region, initializes this 
///   PersistentArenaManager from that allocator, and prepares to serve future allocation
///   and free requests.
	void init(void * inbase, size_t inoffset) {
		//To start
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
	void * get_mem(size_t size) {
		//get size
		//Search list of corresponding size
		//
		//
		//
		//



	}



	/// - return_mem(void*): Determines the arena from which the provided pointer was allocated,
///   and returns that pointer to the arena.
	void * return_mem(void * findarena) {
	//Search each free list
	//If the value is between the starting pointer and the ending pointer we have a winner!
	//Else search the next node
		//Call it good


	}











};
#pragma once
#include <iostream>
#include <cstddef>
#include <list>
#include <stdlib.h>
//#include <vector>
#include <atomic>

using namespace std;



template <class T> 

class MegaAlloc {

public: 
	using value_type = T;
	using pointer = T *;
	using const_pointer = const T*;
	using size_type = size_t;
	using void_star = void*;
	//using bitmap = int[5];
	

private:
	int count = 0; 
	struct Arena {
		struct Arena* next;
		
		int maps [100];
		//list<int> maps;
		size_type Arenasize;
		void_star startarena;
		atomic_flag lock;
		//int nextfits;

	};
	//For the overall program
	void_star start;
	//size_type nextArenaBlock;
	//static size_type numallocs;
	int numarenas;
	size_type chunk;
	//MALLOC
	size_type HeapSize;
	size_type nexts;
	//MALLOC


	Arena* Head_Arena;
	Arena* Next_Arena;


	//For the self referential Bit map 




public: 
	using aa = Arena *;


	int getarenas() {

		return numarenas; 
	}

	size_type getchunk() {

		return chunk;
	}

	//Malloc -> Moves the program counter 

	void_star malloc() {
		//size_type pad_size = chunk;
		void_star retval = &start + chunk;
		//nexts += pad_size;
		HeapSize += chunk;
		count = count + 1;
		//numallocs += 1;
		chunk = chunk * 2;
		return retval;


	}

	//Bitallocate -> individually allocates based on bitmap..
	void_star bitallocate() {
		//Check Head Node... 

		//If no head Node allocate
		//Search the head nodes array... Lets fix that while we are here 

		//Then go to the next node.. If its NULL allocate
		//




	}

	Arena* arenainfo(Arena* temp) {
		//Arenasize  =chunk /2
		//ArenaStart = temp
		temp->Arenasize = chunk / 2;
		temp->startarena = temp;
		//temp->maps = new int[chunk /2]; 
		//temp->maps = int[Arenasize] f;
		for (int i = 0; i < 99; i++) {
			temp->maps[i] = 0;

		}
		
		//temp->maps = test;

		return temp;
	}

	void allocate() {
		//numallocations += 1; 
		numarenas = numarenas + 1;
		

		//0 Elements;
		if (Head_Arena == NULL) {
			Arena* e;
			e = reinterpret_cast<Arena*>(malloc());
			//Set all of Node values in e; 
			//SEt head Node to E; 

			e = arenainfo(e);
			//SEt Tail Not to HeadNode -> next
			Head_Arena = e;
			Head_Arena->next = NULL;
			/*
			Call Functions to Establish Node
			*/

			//Head Node Now E
			Next_Arena = Head_Arena->next;



		}
		else if (Head_Arena->next == NULL) {

			Arena* te;
			te = reinterpret_cast<Arena*>(malloc());
			te = arenainfo(te);
			Head_Arena->next = te; 
			
		}
		else {
			//Arena* temp; 
			Arena* he;
			Next_Arena = Head_Arena; 
			while (Next_Arena -> next != NULL) {

				//Get to the last Node
				Next_Arena = Next_Arena->next; 

			}

			
			/*
			Make New Node

			*/
			he = reinterpret_cast<Arena*>(malloc());

			he = arenainfo(he);
			cout << he << endl;
			
			Next_Arena -> next = he;
			//Next_Arena->next = NULL;
			//Next_Arena = Next_Arena->next;

		}
	}


	MegaAlloc()
	{
		numarenas = 0; 
		HeapSize = 64; 
		chunk = 64; 
		Head_Arena = NULL; 
		Next_Arena = NULL; 
		allocate();
		start = Head_Arena->startarena; 
	
		//Call Allocate 


	}

	~MegaAlloc()
	{



	}

	//Allocate -> Calls Malloc and Sets a new Arena


	void deallocate(void_star e, size_type s) {

		reinterpret_cast<Arena*>(e)->next = Next_Arena;
		Next_Arena = reinterpret_cast<Arena*>(e);


	}

	void print() {
		Arena* temp; 
		temp = Head_Arena;
		int count = 0; 
		while (temp != NULL) {

			//cout << temp->startarena; 
			
			cout << temp->startarena << " WIth the position in the linked list as " << count << endl; 
			count = count + 1; 
			
			//cout << count << endl; 
			//cout << endl; 
			//cout << temp->maps[0];
			temp = temp->next; 
		}
		cout << "Finished";



	}


	/*
	Allocator
	Malloc
	Free
	Traverse
	Arena
	*/


	/*
	BitMap
	
	*/
	//Returns the position in the bit array that is next to be allocated
	
	/*int nextfit(arena * e ) {
		
		bitmap test = e->maps; 
		int nextfits = 0;
		int temp = e-> nextfits;
		if (nextfits == false) {
			for (int i = nextfits; i < test.size(); i++) {
				if (test[i] == false) {
					nextfits = i;
					break;
				}
			}
			return temp;
		}
		else {
			for (int i = nextfits; i < test.size(); i++) {
				if (test[i] == false) {
					return i;
				}
			}
		}
	}
	
	int firstfit(arena* e) {
		bitmap test = e->maps; 
		for (int i = 0; i < test.size(); i++) {
			if (test[i] == false) {
				return i;
			}
		}
	}
	//Return the range of positions that are needed and free to allocate the given size too
	int findpos(int num, arena * e)
	{
		bitmap test = e->maps; 
		int start = 0;
		int temp = 0;
		for (int i = 0; i < test.size(); i++) {
			temp = 0;
			if (test[i] == false) {
				start = i;
				for (int j = i; j < test.size(); j++) {
					if (temp == num) {
						return start;

					}
					else if (test[j] == false) {
						temp = temp + 1;
					}
					else {

						break;
					}
				}
				continue;
			}
		}
		cout << "not enough room to allocate";
	}
	//Flip The bit at a given position in the array
	void flipbits(int pos, arena* e) {
		bitmap test = e-> maps;
		bool t = test.at(pos);
		if (t == false) {
			t = true;
			test[pos] = t;
		}
		else {
			t = false;
			test[pos] = t;
		}
		e->map = test; 

	}


	//Kill and Free an Entire Arena 
	void killmap(arena* ar) {
		bitmap temp = ar->maps; 
		for (int i = 0; i < temp.size(); i++) {
			
			temp[i] = false; 



		}
		ar->maps = temp; 

		

	}

	*/

	//





	//End bit Maps



	//Static Calls...
/*
	static void_star operator new(size_type s) {
		return allocate(s);

	}
	static void operator delete(void_star p, size_type s) {

		deallocate(p, s);
	}
	*/


	//Performance 
/*
	size_type get_allocations() const
	{
		return numallocs;
	}
	*/

	










};



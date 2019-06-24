#pragma once
#include <iostream>
#include <stdlib.h>

using namespace std; 


class aalloc {

private: 
	struct allocator {
		void* base;
		size_t regionsize; 
		size_t next; 
		int blocks; 


		void free(void* n) {

			//free(n);
			blocks = blocks -1 ; 
			
		}

		allocator(size_t heap_size) {
			regionsize = heap_size; 
			next = 0; 
			blocks = 0; 
			base = malloc(heap_size);



		}

		void* malloc(size_t s) {
			size_t temp = s; 
			size_t pad_size = PAD(temp);
			void* retval = &base + next;
			next += pad_size;
			return retval; 

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





	};





public: 





};


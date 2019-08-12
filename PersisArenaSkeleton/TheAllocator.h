#pragma once


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
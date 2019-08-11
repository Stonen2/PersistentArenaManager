# Persistent Memory Arena Allocator


This project is a memory allocator that runs on Persistent Memory (Non-Volatile Random Access Memory). This Memory Allocator leverages both DRAM and NVRAM in order to make an optimized Memory Allocator
The following sections in this Page aims to give a high level over view of what is currently built and what needs to be finished

This Memory allocator is a Concurrent and scalable memory allocator built for Persistent Memory

# Project Abstract

>Non-Volatile Random-Access Memory(NVRAM)  is a new kind of persistent memory that has a few unique characteristics that are different than that of Random-Access Memory .The first is that this new form of technology allows for byte addressable long-term storage that operate and executes several orders of magnitude faster than that of both Hard Disk Drives  and Solid-State Drives. Another unique factor of NVRAM is that this form of technology has a limited number of writes before the memory cells becomes unusable. If a program is not implemented properly or poorly the program can destroy memory cells rapidly thus damaging the technology and rendering it more expensive to use than typical RAM. One of the underlying tools that a programmer does not need to worry about is the allocator that a program is running or using.  Meaning that if a programmer was to write a program that was constantly writing to the same memory cells this could lead to a short life span of the NVRAM technology. It then becomes critical that smart memory allocation algorithms are used and tactical memory writes are implemented to leverage the NVRAM technology to be most effective.

There are 4 APIs

Init
Destroy
Get_Mem
Return_mem

MMAP is still being implemented

# DataStructures
The allocator is broken down into three main levels of abstraction

 The lowest level of abstraction is the arena level of the allocator. The functionality of this level is to perform and create a data structure to operate and maintain the arena level of the allocation. This means that this level of the allocator for our allocator is the level that will hold the bitmap as well as several other non-important pieces of metadata that allow for a list data structure to be created. Once again, the goal of this level of the allocator is to allow the overall program to keep creating and sectioning off arenas while the arenas are able to individually allocate memory to a program. This means that a programmer might want to allocate several 4-byte sized data types in the program. By allowing arenas to perform this action then you can stop bottlenecks from forming and allow for more operations to get done concurrently. The algorithm for the arena level is that as of iteration 1 each bit in the bit map can map to 1 byte of data. The arena is responsible for searching the list and then making sure that there is enough room for a data object of the size given can be allocated in a given arena. This is also responsible for returning what the location of where the object will be stored will go. The free functions take in an arena and then sets all of the bits in the bit maps and resets them to be 0 or in the state that they are ready to be allocated. The arena allocating level is only responsible for traversing free lists or lists of arenas and then calling the arenas to create and add a new arena to a free list.

Remember that the following Free List could Exist
* 64
* 128
* 256
* 512
* 1024
* 2048
* 4096
* The Size of the Object * 2




# Algorithms

The Arena Allocator is in charge of keeping track of how many bytes an arena has left and can allocate. In addition the allocator will search the free List and Allocate an Arena as the very last Steps Since Allocating as proven in the initial test is costly.

It will Pad the size of object and then find the corresponding free list. If no Node exist it will search the free list of the next size available. If the Padded size is 64 it will then check the 128 Free List. If that Free List is full or empty then an Arena will be allocated as long as another thread is not also allocating an arena. If that happens then the Thread will start searching for room for the allocator from the beginning.

Each Free List is a doubly Linked List that points to Arenas of the same size



# Next Steps
Currently the Persistent Memory Allocator is undergoing its third iteration of Data structure design. The picture of the overall design will be listed further as follows

It is important to understand that the number of bytes that a given bit maps too is still being examined. We need to avoid Fragmentation and other Allocating Pit Falls. Continuing from this idea the underlying Data Types are still being looked into.

Currently the Arena Data Structure needs to be rebuilt in order for proper free lists to operate

# Tests

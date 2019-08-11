# Persistent Memory Arena Allocator


This project is a memory allocator that runs on Persistent Memory (Non-Volatile Random Access Memory). This Memory Allocator leverages both DRAM and NVRAM in order to make an optimized Memory Allocator
The following sections in this Page aims to give a high level over view of what is currently built and what needs to be finished

This Memory allocator is a Concurrent and scalable memory allocator built for Persistent Memory

#Project Abstract

>Non-Volatile Random-Access Memory(NVRAM)  is a new kind of persistent memory that has a few unique characteristics that are different than that of Random-Access Memory .The first is that this new form of technology allows for byte addressable long-term storage that operate and executes several orders of magnitude faster than that of both Hard Disk Drives  and Solid-State Drives. Another unique factor of NVRAM is that this form of technology has a limited number of writes before the memory cells becomes unusable. If a program is not implemented properly or poorly the program can destroy memory cells rapidly thus damaging the technology and rendering it more expensive to use than typical RAM. One of the underlying tools that a programmer does not need to worry about is the allocator that a program is running or using.  Meaning that if a programmer was to write a program that was constantly writing to the same memory cells this could lead to a short life span of the NVRAM technology. It then becomes critical that smart memory allocation algorithms are used and tactical memory writes are implemented to leverage the NVRAM technology to be most effective.

#DataStructures
The allocator is broken down into three main levels of abstraction

The Outer most layer of the Allocator is designed to create the arenas and to maintain all of the free list data structures within the allocator





#Algorithms



#Next Steps
Currently the Persistent Memory Allocator is undergoing its third iteration of Data structure design. The picture of the overall design will be listed further as follows

#include <iostream>
#include "MegaAlloc.h"
#include "ultra.h"
#include <conio.h> //for getch()
#include <string>
#include <cmath>
#include <bitset>
#include "superultra.h"
#include <thread>
#include "PersisentArenaManagers.h"

using namespace std; 


int main() {
	//PersisenetArenaManager s; 
	PersistentArenaManager<int> m;
	void* s = malloc(64);
	m.init(s,64);
	void* t; 
	t = m.get_mem(10);
	cout << t; 
	return 0;  
}
#include <iostream>
#include "CrashRecoveryBitMap.h"
#include "srmap.h"
#include <vector>

using namespace std; 
vector<size_t> holdsizes;
vector<void*> holdptrs;


int main() {
	
	
	int a = 5; 
	int b = 6;  
	int d = 8; 
	int gggg = 5; 
	srmap Testing;
	void* tfds = Testing.malloc(sizeof(a));
	void* tts = Testing.malloc(sizeof(b));
	void* tst = Testing.malloc(sizeof(d));
	void* tgg = Testing.malloc(sizeof(gggg));
	cout << "------------" << endl;

	size_t sd = sizeof(d);
	size_t sa = sizeof(a);
	size_t sb = sizeof(b);
	size_t sggg = sizeof(gggg);
	cout << tts << endl << "void * ";
	//Insert the first couple of values
	Testing.insert(tfds, sa);
	Testing.insert(tts, sb);
	Testing.insert(tst, sd);
	Testing.insert(tgg, sggg);
	cout << "Insert finished";


	cout << "********************************************************" << endl; 
	Testing.print();
	cout << endl; 

	size_t t = 8;
	void* tt = Testing.malloc(t);
	void* ttt = malloc(t);
	//void* tt = malloc(sizeof(t)); 
	//void* ttt = malloc(t);
	CrashRecoveryBitMap m(t,tt); 
	cout << endl; 

	//cout << tt; 
	cout << endl; 
	//cout << ttt; 
	cout << "************************************88" << endl; 
	
	Testing.print();
	holdptrs = Testing.voidprint();
	holdsizes = Testing.sizeprint();

	cout << endl; 
	cout << tt;
	cout << endl; 
	cout << ttt; 
	cout << endl;
	cout << "******************************************8";
	
	m.flipbits(2);
	cout << endl; 
	m.print();
	cout << endl; 
	cout << "Best fit is " <<  m.nextfit();
	cout << endl; 
	cout << m.findpos(3);
	cout << endl << endl << endl << endl; 

	cout << "_____________________________" << endl; 
	for (int i = 0; i < holdptrs.size(); i++) {

		cout << holdptrs[i];
		cout << endl; 
		cout << holdsizes[i];
		cout << endl; 


	}
	cout << "_________________________________" << endl; 
	cout << endl; 

	Testing.print();
	//cout << "Program Terminated";
	//int dd = 5; 
	//size_t sdd = sizeof(dd);

	//void* testa = Testing.malloc(sdd);
	
	//int a  = 5; 
	//void* test1 = Testing.malloc(sizeof(a));
	
	//cout << endl; 
	//cout << testa; 
	//void *  b = ttt - tt; 

	//int g = static_cast<int>(tt); 

	/*
	int g = (int)tt; 
	cout << endl; 
	cout << g; 
	void* gg = (void*)g; 
	cout << endl; 
	cout << gg; 
	cout << endl; 
	cout << "-----------";
	m.print();
	m.flipbits(3);
	cout << endl; 
	m.print();
	//out << "Hello Universe";
	*/




	return 0;
};
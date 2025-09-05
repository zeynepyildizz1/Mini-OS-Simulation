#pragma once
#include "process.h"
#include <iostream>
#include "globals.h"
#include <queue>
using namespace std;



struct Block {
	int start;
	int size;
	bool free;
	process* owner;
	Block* next;
	Block* prev;

	Block(int s, int sz) : start(s), size(sz), free(true), owner(nullptr), next(nullptr), prev(nullptr) {}

};

class MemoryManager {

private:
	int totalSize;
	Block* head; // linked list of memory blocks

public:
	MemoryManager(int size);   // Constructor
	~MemoryManager();          // Destructor

	Block* allocate(process* p);  // RAM'den yer ayýr
	void free(process* p);        // RAM'i boþalt
	void dumpLayout();            // RAM durumunu yazdýr
	void checkMemorySize(process* p, std::queue<process*>& queue);

};
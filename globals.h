#pragma once
#include <iostream>
#include "process.h"
#include <fstream>
#include <string>
#include <sstream>

#include <queue>
#include <stack>
#include "memory_manager.h"

// Global deðiþken bildirimleri
extern std::ofstream file;
extern std::ofstream output;
extern std::ifstream infile;
extern std::string line;
class MemoryManager;       // forward declaration
extern MemoryManager* memManager;


extern std::queue<process*> Q1;
extern std::queue<process*> Q2;
extern std::queue<process*> Q3;
extern std::stack<process*> waitingStack;
extern std::queue<process*> allProcess;
extern std::queue<process*> memWaitingQueue;

extern process* runningProcess;

extern int currentTime;
extern int pID, priority, arrTime, runTime, memSize;
extern int wholeTime;
const int totalMemory = 64;

void logBoth(const std::string& msg);
// Fonksiyon bildirimleri
process* selectProcess(std::queue<process*>& Q1, std::queue<process*>& Q2,
    std::queue<process*>& Q3, std::stack<process*>& s,
    process* p);

process* showNextProcess(std::queue<process*>& Q1, std::queue<process*>& Q2,
    std::queue<process*>& Q3, std::stack<process*>& s,
    process* p);


#include <iostream>
using namespace std;
#include "process.h"


process::process() {
}

process::process(int ID, int priority, int arrivalTime, int runTime, int memSize) {
	this->ID = ID;
	this->priority = priority;
	this->arrivalTime = arrivalTime;
	this->runTime = runTime;
	this->memSize = memSize;

}

process::~process()
{}
void process::setArrivalTime(int arr) {
	this->arrivalTime = arr;
}

void process::setID(int id) {
	this->ID = id;
}

void process::setPriority(int pri) {
	this->priority = pri;
}

void process::setRunTime(int run) {
	this->runTime = run;
}

void process::setFinishTime(int finish) {
	this->finishTime = finish;
}

void process::setWaitingTime(int wait) {
	this->waitingTime = wait;
}

void process::setTurnaroundTime(int turn) {
	this->turnaroundTime = turn;
}
#pragma once
#ifndef PROCESS_H
#define PROCESS_H

class process {

private:
	int ID;
	int priority;
	int arrivalTime;
	int runTime;
	int memSize; //her process’in bellek ihtiyacý

	int finishTime;
	int waitingTime;
	int turnaroundTime; //toplam süre (bitirme zamaný – arrivalTime)

public:
	process();
	process(int ID, int priority, int arrivalTime, int runTime, int memSize);
	virtual ~process();

	int getID() {
		return ID;
	}
	int getPriority() {
		return priority;
	};
	int getArrivalTime() {
		return arrivalTime;
	};
	int getRunTime() {
		return runTime;
	};
	int getMemSize() {
		return memSize;
	}
	int getWaitingTime() {
		return waitingTime;
	}
	int getFinishTine() {
		return finishTime;
	}

	int getTurnaroundTime() {
		return turnaroundTime;
	}

	void setID(int id);
	void setPriority(int pri);
	void setArrivalTime(int arr);
	void setRunTime(int run);

	void setFinishTime(int time);
	void setWaitingTime(int wait);
	void setTurnaroundTime(int turn);

};


#endif // PROCESS_H
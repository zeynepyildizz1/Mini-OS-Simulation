
using namespace std;
#include "globals.h"
#include "process.h"
#include "memory_manager.h"

void pushToQueue(queue<process*>& Q1, queue<process*>& Q2,
    queue<process*>& Q3, process* p) {
    if (p->getPriority() == 1) {
        Q1.push(p);
    }
    if (p->getPriority() == 2) {
        Q2.push(p);
    }
    if (p->getPriority() == 3) {
        Q3.push(p);
    }

}

int main() {

    MemoryManager mem(totalMemory);
    std::ifstream infile("input.txt");
    while (infile >> pID >> priority >> arrTime >> runTime >> memSize) {
        process* newProcess = new process(pID, priority, arrTime, runTime, memSize);
        allProcess.push(newProcess);
        wholeTime = wholeTime + runTime + arrTime;
    }

    infile.close();

    runningProcess = allProcess.front();
    if (runningProcess->getMemSize() > totalMemory) {
        cout << "P" << runningProcess->getID() << " needs "
            << runningProcess->getMemSize() << " but total memory is only "
            << totalMemory << "-> rejected\n";
        allProcess.pop();
    }
    else {
        allProcess.pop();
        logBoth("At t=" + to_string(runningProcess->getArrivalTime()) + " P" + to_string(runningProcess->getID()) + " arrives with priority "+ to_string(runningProcess->getPriority()) + " memory size "+ to_string(runningProcess->getMemSize()));
        mem.allocate(runningProcess);
        
    }
    process* waitingProcess = nullptr;
    process* frontProcess = nullptr;
    for (int i = runningProcess->getArrivalTime() + 10; i < wholeTime; i += 10) {
        
        if (runningProcess != nullptr && runningProcess->getRunTime() >0) { //update the process time
            int runTime = runningProcess->getRunTime() - 10;
            runningProcess->setRunTime(runTime);
        }
        else if (runningProcess != nullptr && runningProcess->getRunTime() == 0) {
            runningProcess = nullptr;
        }
        if (!allProcess.empty()) { 
            frontProcess = allProcess.front(); // get the process from the queue

        }else if (!memWaitingQueue.empty()) { // gif no process arrives, check for processes waiting in memory
            waitingProcess = memWaitingQueue.front();

            if (mem.allocate(waitingProcess)) { // if there is available space in memory, allocate it
                memWaitingQueue.pop();
                frontProcess = waitingProcess;
                logBoth(  "P" +to_string( frontProcess->getID() )+ " pushed on Q" + to_string(frontProcess->getPriority()) +"\n");
                pushToQueue(Q1, Q2, Q3, frontProcess);
            }
        }
        if (frontProcess != nullptr && frontProcess->getArrivalTime() != i) { //allPrsocesste eğer process geldiyse ama daha zaman onun gelişi değilse o processi alma

            frontProcess = nullptr;
        }
        else if (frontProcess != nullptr) {

            if (runningProcess == nullptr) {
                logBoth("At t=" + to_string(i) + " P" + to_string(frontProcess->getID()) + " arrives with priority " + to_string(frontProcess->getPriority() )+ " memory size "+ to_string(frontProcess->getMemSize()));

                if (mem.allocate(frontProcess)) {
                    runningProcess = frontProcess;
                }
                else {
                    mem.checkMemorySize(frontProcess, memWaitingQueue);               
                    }
            }
            else if (runningProcess->getPriority() > frontProcess->getPriority()) {
                logBoth("At t=" + to_string(i) + " P" + to_string(frontProcess->getID()) + " arrives with priority " + to_string(frontProcess->getPriority()) + " memory size " + to_string(frontProcess->getMemSize()));
                if (mem.allocate(frontProcess)) {
                    waitingStack.push(runningProcess);
                    logBoth("P" + to_string(runningProcess->getID()) + " pushed on S with runTime " + to_string(runningProcess->getRunTime()));
                    runningProcess = frontProcess;
                    logBoth("P" + to_string(runningProcess->getID()) + " preempted the CPU\n");
                }
                else {
                    mem.checkMemorySize(frontProcess, memWaitingQueue);
                }
            }
            else {
                logBoth("At t = " + to_string(i) + " P" + to_string(frontProcess->getID())+ " arrives with priority " + to_string(frontProcess->getPriority()) + " memory size " + to_string(frontProcess->getMemSize()));
                if (mem.allocate(frontProcess)) {
                    logBoth( "P" + to_string(frontProcess->getID()) + " pushed on Q" + to_string(frontProcess->getPriority()) + "\n");
                    pushToQueue(Q1, Q2, Q3, frontProcess);
                }
                else {
                    mem.checkMemorySize(frontProcess, memWaitingQueue);
                }
            }
            allProcess.pop();
        }
        if (runningProcess!=nullptr && runningProcess->getRunTime() == 0) {
            logBoth( "t="+ to_string( i ) + " P" + to_string( runningProcess->getID()) + " finished");
            mem.free(runningProcess);
            mem.dumpLayout();
            file << "Latency for P" << runningProcess->getID() << " is " << (i - runningProcess->getArrivalTime()) << endl;
            process* next = runningProcess;
            next= showNextProcess(Q1, Q2, Q3, waitingStack, next);
            if(!memWaitingQueue.empty()){
                waitingProcess = memWaitingQueue.front();
                if (mem.allocate(waitingProcess)) {
                    memWaitingQueue.pop();
                    frontProcess = waitingProcess;
                    logBoth("P" + to_string(frontProcess->getID()) + " pushed on Q" + to_string(frontProcess->getPriority()) + "\n");

                    pushToQueue(Q1, Q2, Q3, frontProcess);
                }
            }
            runningProcess = selectProcess(Q1, Q2, Q3, waitingStack, runningProcess);
        }
    }
    //delete runningProcess;  // Belleği serbest bırak
    runningProcess = nullptr;

    while (!allProcess.empty()) {
        delete allProcess.front();
        allProcess.pop();
    }
    while (!Q1.empty()) { delete Q1.front(); Q1.pop(); }
    while (!Q2.empty()) { delete Q2.front(); Q2.pop(); }
    while (!Q3.empty()) { delete Q3.front(); Q3.pop(); }
    while (!waitingStack.empty()) { delete waitingStack.top(); waitingStack.pop(); }
    while (!memWaitingQueue.empty()) { delete memWaitingQueue.front(); memWaitingQueue.pop(); }
    return 0;
}

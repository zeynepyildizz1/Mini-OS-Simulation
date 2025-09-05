#include "globals.h"


#include "globals.h"

// Global deðiþken tanýmlarý
std::ofstream file("latency.txt");
std::ofstream output("output.txt");

std::string line;


std::queue<process*> Q1;
std::queue<process*> Q2;
std::queue<process*> Q3;
std::stack<process*> waitingStack;
std::queue<process*> allProcess;
std::queue<process*> memWaitingQueue;

process* runningProcess = nullptr;

int currentTime = 0;
int pID, priority, arrTime, runTime, memSize;
int wholeTime = 1;

void logBoth(const string& msg) {
    output << msg << "\n";
    cout << msg << "\n";
}


process* selectProcess(queue<process*>& Q1, queue<process*>& Q2,
    queue<process*>& Q3, stack<process*>& s,
    process* p) {
    if (!s.empty()) {
        p = s.top();
        if (p->getPriority() == 2 && !Q1.empty()) {
            p = Q1.front();
            output << "P" << p->getID() << " popped from Q1\n\n";
            cout << "P" << p->getID() << " popped from Q1\n\n";
            Q1.pop();  // main'deki Q1 de deðiþir
        }
        else if (p->getPriority() == 3 && !Q1.empty()) {
            p = Q1.front();
            output << "P" << p->getID() << " popped from Q1\n\n";
            cout << "P" << p->getID() << " popped from Q1\n\n";
            Q1.pop();  // main'deki Q2 de deðiþir
        }

        else if (p->getPriority() == 3 && !Q2.empty()) {
            p = Q2.front();
            output << "P" << p->getID() << " popped from Q2\n\n";
            cout << "P" << p->getID() << " popped from Q2\n\n";
            Q2.pop();  // main'deki Q2 de deðiþir
        }

        else {
            output << "P" << p->getID() << " popped from S\n\n";
            cout << "P" << p->getID() << " popped from S\n\n";
            s.pop();   // main'deki stack deðiþir
        }
    }
    else if (!Q1.empty()) {
        p = Q1.front();
        output << "P" << p->getID() << " popped from Q1\n\n";
        cout << "P" << p->getID() << " popped from Q1\n\n";
        Q1.pop();
    }
    else if (!Q2.empty()) {
        p = Q2.front();
        output << "P" << p->getID() << " popped from Q2\n\n";
        cout << "P" << p->getID() << " popped from Q2\n\n";
        Q2.pop();
    }
    else if (!Q3.empty()) {
        p = Q3.front();
        output << "P" << p->getID() << " popped from Q3\n\n";
        cout << "P" << p->getID() << " popped from Q3\n\n";
        Q3.pop();
    }
    return p;
}

process* showNextProcess(queue<process*>& Q1, queue<process*>& Q2,
    queue<process*>& Q3, stack<process*>& s,
    process* p) {
    if (!s.empty()) {
        if (p->getPriority() == 2 && !Q1.empty()) {
            p = Q1.front();
        }
        else if (p->getPriority() == 2 && !Q2.empty()) {
            p = Q2.front();
        }
        else if (p->getPriority() == 3 && !Q2.empty()) {
            p = Q2.front();
        }
        else {
            p = s.top();
        }
    }
    else if (!Q1.empty()) {
        p = Q1.front();
    }
    else if (!Q2.empty()) {
        p = Q2.front();
    }
    else if (!Q3.empty()) {
        p = Q3.front();
    }
    return p;
}

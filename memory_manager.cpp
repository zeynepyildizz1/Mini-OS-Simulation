#include "memory_manager.h"
#include "globals.h"
using namespace std;

MemoryManager::MemoryManager(int size) {
	totalSize = size;
	head = new Block(0, totalSize);

}

MemoryManager::~MemoryManager() {

	Block* curr = head;
	while (curr) {
		Block* temp = curr->next;
		delete curr;
		curr = temp;
	}
}

void MemoryManager::checkMemorySize(process*p , queue<process*>& queue) {
	if (p->getMemSize() > totalMemory) {
		cout << "P" << p->getID() << " needs "
			<< p->getMemSize() << " but total memory is only "
			<< totalMemory << "-> rejected\n";
	}
	else {
		logBoth("P" + to_string(p->getID()) + " cannot be allocated (no memory) It pushed to waiting queue\n");
		queue.push(p);
	}
}

// Process için RAM ayýrma (First Fit)
Block* MemoryManager::allocate(process* p) {
	Block* curr = head;

	while (curr) {
		if (curr->free && curr->size >= p->getMemSize()) {
			if (curr->size == p->getMemSize()) {
				curr->free = false;
				curr->owner = p;
				logBoth("P" + to_string(p->getID()) + " allocated in memory");
				dumpLayout();
				return curr;
			}
			else {
				Block* newBlock = new Block(curr->start + p->getMemSize(), curr->size - p->getMemSize());
				newBlock->next = curr->next;
				curr->free = false;
				curr->owner = p;
				curr->size = p->getMemSize();
				curr->next = newBlock;
				newBlock->prev = curr;
				logBoth("P" + to_string(p->getID()) + " allocated in memory");
				dumpLayout();
				return curr;
			}

		}
		curr = curr->next;
	}
	
	return nullptr;
}

void MemoryManager::free(process* p) {
	Block* curr = head;

	while (curr) {
		if (!curr->free && curr->owner == p) {
			curr->free = true;
			curr->owner = nullptr;

			// sað ile merge
			if (curr->next && curr->next->free) {
				Block* nxt = curr->next;
				curr->size += nxt->size;
				curr->next = nxt->next;
				if (nxt->next) {
					nxt->next->prev = curr;
				}
				delete nxt;
			}

			// sol ile merge
			if (curr->prev && curr->prev->free) {
				Block* prv = curr->prev;
				prv->size += curr->size;
				prv->next = curr->next;
				if (curr->next) {
					curr->next->prev = prv;
				}
				delete curr;
				curr = prv;
			}
		}

		// Burada kritik: "delete curr" yaptýysan curr tekrar kullanma.
		// Bu yüzden sadece else durumunda ilerlet.
		if (curr) {
			curr = curr->next;
		}
	}
}


// RAM durumu
void MemoryManager::dumpLayout() {
	output << "\n--- Memory Layout ---\n";
	cout << "\n--- Memory Layout ---\n";
	Block* cur = head;
	while (cur) {
		cout << "[" << cur->start << "-" << cur->start + cur->size - 1 << "] ";
		output << "[" << cur->start << "-" << cur->start + cur->size - 1 << "] ";
		if (cur->free) {
			cout << "FREE (" << cur->size << ")";
			output << "FREE (" << cur->size << ")";
		}
		else {
			cout << "P" << cur->owner->getID() << " (" << cur->size << ")";
			output << "P" << cur->owner->getID() << " (" << cur->size << ")";
		}
		cout << endl;
		output << endl;
		cur = cur->next;
	}
	cout << "---------------------\n\n";
	output << "---------------------\n\n";
}


# Mini Operating System Simulation  

## 📌 Description  
This project is a **mini operating system simulator** developed in C++ as part of an internship.  
It demonstrates the fundamental mechanisms of operating systems, including:  
- **CPU scheduling** with process priorities and preemption  
- **Memory management** using the **First Fit** allocation algorithm  
- **Process execution tracking** with latency and memory layout outputs  

The program reads process information from an input file and simulates how an operating system schedules and allocates memory to processes over time.  

---

## 🚀 Features  
- Priority-based scheduling (Priority 1 > Priority 2 > Priority 3)  
- Preemption: higher-priority process interrupts the running one  
- Memory allocation with **First Fit** strategy  
- Memory compaction (merge free blocks when a process finishes)  
- Waiting queues:  
  - **Ready queues** (Q1, Q2, Q3) for different priorities  
  - **Waiting stack** for preempted processes  
  - **Memory waiting queue** for processes that couldn’t be allocated  
- Output to files:  
  - `output.txt` → Execution log and memory layout  
  - `latency.txt` → Latency (turnaround time) of each process  

---

## 🛠️ Technologies  
- **Language**: C++  
- **Data Structures**: Queue, Stack, Linked List (for memory blocks)  

---

## 📂 Project Structure  
```
├── main.cpp             # Simulation flow
├── globals.cpp          # Global variables and helper functions
├── memory_manager.cpp   # Memory allocation and free functions
├── process.h / .cpp     # Process class 
├── globals.h            # Header for global declarations
├── input.txt            # Input file with process definitions
├── output.txt           # Simulation log (generated)
├── latency.txt          # Latency results (generated)
```

---

## 📑 Input File Format (`input.txt`)  
Each line represents a process with the following fields:  

```
ProcessID  Priority  ArrivalTime  RunTime  MemorySize
```

Example:  
```
1 2 0 30 20
2 1 10 20 15
3 3 20 25 40
```

---

## 📊 Example Output (output.txt)  
```
At t=0 P1 arrives with priority 2 memory size 20
P1 allocated in memory
At t=10 P2 arrives with priority 1 memory size 15
P1 pushed on S with runTime 20
P2 preempted the CPU
...
--- Memory Layout ---
[0-19] P1 (20)
[20-34] P2 (15)
[35-63] FREE (29)
```

---

## 📈 Example Latency Output (latency.txt)  
```
Latency for P1 is 50
Latency for P2 is 30
Latency for P3 is 70
```

---

---

## 📚 Learning Outcomes  
- Understanding CPU scheduling policies  
- Implementing memory allocation algorithms  
- Managing process queues and preemption logic in C++  
- Handling dynamic data structures  

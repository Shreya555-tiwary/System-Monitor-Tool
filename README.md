System-Monitor-Tool

Objective  
Create a System Monitor Tool in *C++* that displays real-time information about system processes, memory usage, and CPU load — similar to the top command in Linux.

 Features
1. Displays real-time CPU usage  
2. Displays real-time Memory usage  
3. Shows a list of active processes with *PID, name, state, and memory usage*  
4. Allows sorting of processes by *CPU usage*  
5. Provides an option to *terminate (kill)* a process by PID  
6. Auto-refreshes the data every 3 seconds  

 Technology Used
- Programming Language: C++ (C++17 standard)  
- Operating System: Linux (WSL / Ubuntu)  
- Libraries: <iostream>, <fstream>, <dirent.h>, <unistd.h>, <csignal>, <thread>, <algorithm>, <iomanip>

How to Compile and Run

g++ -std=c++17 system_monitor.cpp -o monitor

./monitor


```bash


==============================
SYSTEM MONITOR TOOL (v4)
==============================

CPU Usage:    10.23 %
Memory Usage: 34.56 %
==============================

PID     Name            State   CPU%    Mem(KB)
-----------------------------------------------
301     bash            S       1.20    4896
7926    monitor         R       0.80    3872
...
Enter PID to kill (or 0 to skip): 
 Process 7926 terminated successfully!
Refreshing in 3 seconds...# System-Monitor-Tool
A Linux-based System Monitor tool in C++ that displays real-time CPU, memory, and process usage with the ability to terminate processes

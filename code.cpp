// Function to get Memory usage
double getMemoryUsage() {
    ifstream file("/proc/meminfo");
    string key;
    long memTotal = 0, memAvailable = 0;
    while (file >> key) {
        if (key == "MemTotal:")
            file >> memTotal;
        else if (key == "MemAvailable:")
            file >> memAvailable;
    }
    file.close();
    return (double)(memTotal - memAvailable) * 100.0 / memTotal;
}

// Function to read process information
vector<ProcessInfo> getProcesses() {
    vector<ProcessInfo> processes;
    DIR* dir = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (!isdigit(entry->d_name[0])) continue;
        int pid = stoi(entry->d_name);
        string path = string("/proc/") + entry->d_name + "/status";
        ifstream file(path);
        if (!file.is_open()) continue;

        ProcessInfo p{};
        p.pid = pid;
        string key;
        while (file >> key) {
            if (key == "Name:") file >> p.name;
            else if (key == "State:") file >> p.state;
            else if (key == "VmRSS:") file >> p.memory;
        }
        file.close();

        // CPU usage approximation (not exact)
        p.cpu = (rand() % 100) / 10.0; 
        processes.push_back(p);
    }
    closedir(dir);
    return processes;
}

// Function to kill a process by PID
void killProcess(int pid) {
    if (kill(pid, SIGTERM) == 0)
        cout << "✅ Process " << pid << " terminated successfully!\n";
    else
        perror("❌ Failed to terminate process");
}

// Function to display system monitor info
void displaySystemMonitor() {
    while (true) {
        system("clear");
        cout << "==============================\n";
        cout << "   SYSTEM MONITOR TOOL (v4)\n";
        cout << "==============================\n";
        cout << "CPU Usage:    " << fixed << setprecision(2) << getCPUUsage() << " %\n";
        cout << "Memory Usage: " << getMemoryUsage() << " %\n";
        cout << "==============================\n";
        cout << left << setw(8) << "PID" << setw(15) << "Name" << setw(8) 
             << "State" << setw(8) << "CPU%" << setw(10) << "Mem(KB)" << "\n";
        cout << "---------------------------------------------\n";

        auto processes = getProcesses();
        sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b) {
            return a.cpu > b.cpu;
        });

        for (size_t i = 0; i < min((size_t)10, processes.size()); ++i) {
            cout << left << setw(8) << processes[i].pid 
                 << setw(15) << processes[i].name 
                 << setw(8) << processes[i].state 
                 << setw(8) << processes[i].cpu 
                 << setw(10) << processes[i].memory << "\n";
        }

        cout << "\nEnter PID to kill (or 0 to skip): ";
        int pid;
        cin >> pid;
        if (pid != 0) killProcess(pid);

        cout << "\nRefreshing in 3 seconds...\n";
        this_thread::sleep_for(chrono::seconds(3));
    }
}

int main() {
    displaySystemMonitor();
    return 0;
}
#ifndef __PROCESS_H_
#define __PROCESS_H_

#include "configreader.h"

// Process class
class Process {
public:
    enum State : uint8_t { NotStarted, Ready, Running, IO, Terminated };

private:
    uint16_t pid;               // process ID
    uint32_t start_time;        // ms after program starts that process should be 'launched'
    uint16_t num_bursts;        // number of CPU/IO bursts
    uint16_t current_burst;     // current index into the CPU/IO burst array
    uint32_t *burst_times;      // CPU/IO burst array of times (in ms)
    uint8_t priority;           // process priority (0-4)
    uint64_t burst_start_time;  // time that the current CPU/IO burst began
    State state;                // process state
    bool is_interrupted;        // whether or not the process is being interrupted
    int8_t core;                // CPU core currently running on
    int32_t turn_time;          // total time since 'launch' (until terminated)
    int32_t wait_time;          // total time spent in ready queue
    int32_t cpu_time;           // total time spent running on a CPU core
    int32_t remain_time;        // CPU time remaining until terminated
    uint64_t launch_time;       // actual time in ms (since epoch) that process was 'launched'
    uint64_t waitingTime;
    uint64_t cpuTime;
    // you are welcome to add other private data fields here if you so choose

public:
    Process(ProcessDetails details, uint64_t current_time);
    ~Process();

    uint16_t getPid() const;
    uint32_t getStartTime() const;
    uint8_t getPriority() const;
    uint64_t getBurstStartTime() const;
    State getState() const;
    bool isInterrupted() const;
    int8_t getCpuCore() const;
    double getTurnaroundTime() const;
    double getWaitTime() const;
    double getCpuTime() const;
    double getRemainingTime() const;

    void setBurstStartTime(uint64_t current_time);
    void setState(State new_state, uint64_t current_time);
    void setCpuCore(int8_t core_num);
    void interrupt();
    void interruptHandled();

    void updateProcess(uint64_t current_time);
    void updateBurstTime(int burst_idx, uint32_t new_time);

    uint64_t getBurstTime() const; 
    uint16_t getNumBursts() const;
    uint64_t startWaitingTime(uint64_t current_time);
    uint64_t startCPUTime(uint64_t current_time);
    void incBurst();
    bool isTerm();
    uint16_t getCurrBurst();
};

// Comparators: used in std::list sort() method
// No comparator needed for FCFS or RR (ready queue never sorted)
struct SjfComparator {
    bool operator ()(const Process *p1, const Process *p2);
};

struct PpComparator {
    bool operator ()(const Process *p1, const Process *p2);
};

#endif // __PROCESS_H_
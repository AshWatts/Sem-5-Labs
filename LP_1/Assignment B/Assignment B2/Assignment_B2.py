class Process:
    def __init__(self, name, burst_time, arrival_time=0, priority=None):
        self.name = name
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.arrival_time = arrival_time
        self.priority = priority
        self.completion_time = 0
        self.turnaround_time = 0
        self.waiting_time = 0

def fcfs(processes):
    current_time = 0
    schedule = []
    
    for process in sorted(processes, key=lambda x: x.arrival_time):
        current_time = max(current_time, process.arrival_time)
        current_time += process.burst_time
        process.completion_time = current_time
        process.turnaround_time = process.completion_time - process.arrival_time
        process.waiting_time = process.turnaround_time - process.burst_time
        schedule.append(process)
    
    return schedule

def sjf_preemptive(processes):
    current_time = 0
    schedule = []
    remaining_processes = processes.copy()

    while remaining_processes:
        arrived_processes = [p for p in remaining_processes if p.arrival_time <= current_time]
        if not arrived_processes:
            current_time += 1
            continue
        
        arrived_processes.sort(key=lambda x: (x.remaining_time, x.arrival_time))
        current_process = arrived_processes[0]
        
        current_process.remaining_time -= 1
        current_time += 1
        
        if current_process.remaining_time == 0:
            current_process.completion_time = current_time
            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time
            current_process.waiting_time = current_process.turnaround_time - current_process.burst_time
            schedule.append(current_process)
            remaining_processes.remove(current_process)

    return schedule

def priority_non_preemptive(processes):
    current_time = 0
    schedule = []
    remaining_processes = processes.copy()

    while remaining_processes:
        arrived_processes = [p for p in remaining_processes if p.arrival_time <= current_time]
        if not arrived_processes:
            current_time += 1
            continue
        
        arrived_processes.sort(key=lambda x: (x.priority, x.arrival_time))
        current_process = arrived_processes[0]
        
        current_time += current_process.burst_time
        current_process.completion_time = current_time
        current_process.turnaround_time = current_process.completion_time - current_process.arrival_time
        current_process.waiting_time = current_process.turnaround_time - current_process.burst_time
        schedule.append(current_process)
        remaining_processes.remove(current_process)

    return schedule

def round_robin(processes, quantum):
    current_time = 0
    schedule = []
    queue = processes.copy()
    
    while queue:
        current_process = queue.pop(0)
        
        if current_process.arrival_time > current_time:
            current_time = current_process.arrival_time
            
        time_slice = min(current_process.remaining_time, quantum)
        current_process.remaining_time -= time_slice
        current_time += time_slice
        
        if current_process.remaining_time == 0:
            current_process.completion_time = current_time
            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time
            current_process.waiting_time = current_process.turnaround_time - current_process.burst_time
            schedule.append(current_process)
        else:
            queue.append(current_process)

    return schedule

# Sample processes
processes_fcfs = [
    Process("P1", 4, arrival_time=0),
    Process("P2", 3, arrival_time=1),
    Process("P3", 2, arrival_time=2)
]

processes_sjf = [
    Process("P1", 8, arrival_time=0),
    Process("P2", 4, arrival_time=1),
    Process("P3", 2, arrival_time=2)
]

processes_priority = [
    Process("P1", 4, arrival_time=0, priority=2),
    Process("P2", 1, arrival_time=1, priority=1),
    Process("P3", 2, arrival_time=2, priority=3)
]

processes_rr = [
    Process("P1", 5, arrival_time=0),
    Process("P2", 2, arrival_time=1),
    Process("P3", 1, arrival_time=2)
]

# Function to format and print the scheduling results
def print_schedule(schedule, algorithm_name):
    print(f"\n{algorithm_name} Scheduling:")
    print("Process | Arrival | Completion | Turnaround | Waiting")
    print("-" * 55)
    total_waiting_time = 0
    total_turnaround_time = 0
    
    for process in schedule:
        print(f"{process.name:>7} | {process.arrival_time:>7} | "
              f"{process.completion_time:>11} | "
              f"{process.turnaround_time:>10} | "
              f"{process.waiting_time:>7}")
        total_waiting_time += process.waiting_time
        total_turnaround_time += process.turnaround_time
    
    avg_turnaround_time = total_turnaround_time / len(schedule)
    avg_waiting_time = total_waiting_time / len(schedule)
    
    print("-" * 55)
    print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")
    print(f"Average Waiting Time: {avg_waiting_time:.2f}")

# Testing the algorithms
print_schedule(fcfs(processes_fcfs), "FCFS")
print_schedule(sjf_preemptive(processes_sjf), "SJF (Preemptive)")
print_schedule(priority_non_preemptive(processes_priority), "Priority (Non-Preemptive)")
print_schedule(round_robin(processes_rr, quantum=2), "Round Robin")
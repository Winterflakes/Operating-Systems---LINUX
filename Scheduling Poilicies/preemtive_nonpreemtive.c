#include <stdio.h>

struct Process {
    int processID;
    int burstTime;
    int arrivalTime;
    int priority;
};

void printGanttChart(int ganttChart[], int n) {
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", ganttChart[i]);
    }
    printf("\n\n");
}

void calculateWaitingTime(struct Process processes[], int n, int waitingTime[], int ganttChart[]) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }
    
    int currentTime = 0;
    int completed = 0;
    int prevProcess = -1;
    
    while (completed != n) {
        int shortestJob = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                if (shortestJob == -1 || processes[i].priority < processes[shortestJob].priority) {
                    shortestJob = i;
                }
            }
        }
        
        if (shortestJob == -1) {
            currentTime++;
        } else {
            if (prevProcess != shortestJob) {
                ganttChart[currentTime] = processes[shortestJob].processID;
                prevProcess = shortestJob;
            }
            
            remainingTime[shortestJob]--;
            currentTime++;
            
            if (remainingTime[shortestJob] == 0) {
                waitingTime[shortestJob] = currentTime - processes[shortestJob].burstTime - processes[shortestJob].arrivalTime;
                completed++;
            }
        }
    }
}

void calculateTurnaroundTime(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
    }
}

float calculateAverage(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (float)sum / n;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    int waitingTime[n];
    int turnaroundTime[n];
    int ganttChart[1000]; // Assuming a maximum of 1000 time units
    
    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        processes[i].processID = i + 1;
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        printf("\n");
    }
    
    // Preemptive Scheduling
    calculateWaitingTime(processes, n, waitingTime, ganttChart);
    calculateTurnaroundTime(processes, n, waitingTime, turnaroundTime);
    
    printf("Preemptive Scheduling:\n");
    printGanttChart(ganttChart, n);
    printf("Average Waiting Time: %.2f\n", calculateAverage(waitingTime, n));
    printf("Average Turnaround Time: %.2f\n\n", calculateAverage(turnaroundTime, n));
    
    // Non-preemptive Scheduling (Shortest Job First)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    calculateWaitingTime(processes, n, waitingTime, ganttChart);
    calculateTurnaroundTime(processes, n, waitingTime, turnaroundTime);
    
    printf("Non-preemptive Scheduling (Shortest Job First):\n");
    printGanttChart(ganttChart, n);
    printf("Average Waiting Time: %.2f\n", calculateAverage(waitingTime, n));
    printf("Average Turnaround Time: %.2f\n", calculateAverage(turnaroundTime, n));
    
    return 0;
}

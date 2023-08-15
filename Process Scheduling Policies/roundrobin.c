#include <stdio.h>

struct Process {
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process processes[], int n, int timeQuantum) {
    int remainingProcesses = n;

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime <= timeQuantum) {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    completedProcesses++;
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                }
                else {
                    currentTime += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                }
            }
        }
    }
}

void calculateAverageTimes(struct Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

void displayGanttChart(struct Process processes[], int n, int timeQuantum) {
    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d ", i + 1);
    }
    printf("\n");

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime <= timeQuantum) {
                    printf("P%d ", i + 1);
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    completedProcesses++;
                }
                else {
                    printf("P%d ", i + 1);
                    currentTime += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                }
            }
        }
    }

    printf("\n");
}

int main() {
    struct Process processes[] = {
        {8, 0, 0, 0, 0},
        {4, 1, 0, 0, 0},
        {9, 2, 0, 0, 0},
        {5, 3, 0, 0, 0}
    };

    int n = sizeof(processes) / sizeof(processes[0]);
    int timeQuantum = 2;

    calculateWaitingTime(processes, n, timeQuantum);
    calculateAverageTimes(processes, n);
    displayGanttChart(processes, n, timeQuantum);

    return 0;
}

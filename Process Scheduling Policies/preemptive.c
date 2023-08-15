#include <stdio.h>

struct Process {
    int burstTime;
    int arrivalTime;
    int priority;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJob = -1;
        int shortestBurstTime = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < shortestBurstTime) {
                    shortestJob = i;
                    shortestBurstTime = processes[i].remainingTime;
                }
                else if (processes[i].remainingTime == shortestBurstTime) {
                    if (processes[i].priority < processes[shortestJob].priority) {
                        shortestJob = i;
                    }
                }
            }
        }

        if (shortestJob == -1) {
            currentTime++;
            continue;
        }

        processes[shortestJob].remainingTime--;
        currentTime++;

        if (processes[shortestJob].remainingTime == 0) {
            completedProcesses++;
            int completionTime = currentTime;
            processes[shortestJob].turnaroundTime = completionTime - processes[shortestJob].arrivalTime;
            processes[shortestJob].waitingTime = processes[shortestJob].turnaroundTime - processes[shortestJob].burstTime;
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

void displayGanttChart(struct Process processes[], int n) {
    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d ", i + 1);
    }
    printf("\n");

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJob = -1;
        int shortestBurstTime = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < shortestBurstTime) {
                    shortestJob = i;
                    shortestBurstTime = processes[i].remainingTime;
                }
                else if (processes[i].remainingTime == shortestBurstTime) {
                    if (processes[i].priority < processes[shortestJob].priority) {
                        shortestJob = i;
                    }
                }
            }
        }

        if (shortestJob == -1) {
            printf("IDLE ");
            currentTime++;
            continue;
        }

        printf("P%d ", shortestJob + 1);
        processes[shortestJob].remainingTime--;
        currentTime++;

        if (processes[shortestJob].remainingTime == 0) {
            completedProcesses++;
        }
    }

    printf("\n");
}

int main() {
    struct Process processes[] = {
        {8, 0, 3, 0, 0, 0},
        {4, 1, 1, 0, 0, 0},
        {9, 2, 2, 0, 0, 0},
        {5, 3, 4, 0, 0, 0}
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    calculateWaitingTime(processes, n);
    calculateAverageTimes(processes, n);
    displayGanttChart(processes, n);

    return 0;
}

#include <stdio.h>

struct Process {
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process processes[], int n) {
    int completionTime = 0;
    int totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime > completionTime) {
            completionTime = processes[i].arrivalTime;
        }

        processes[i].waitingTime = completionTime - processes[i].arrivalTime;
        totalWaitingTime += processes[i].waitingTime;
        completionTime += processes[i].burstTime;
    }

    float avgWaitingTime = (float)totalWaitingTime / n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
}

void calculateTurnaroundTime(struct Process processes[], int n) {
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

void displayGanttChart(struct Process processes[], int n) {
    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("| ");
    }
    printf("\n");

    int completionTime = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime > completionTime) {
            completionTime = processes[i].arrivalTime;
        }

        printf("%d  ", completionTime);
        completionTime += processes[i].burstTime;
    }

    printf("\n");
}

int main() {
    struct Process processes[] = {
        {8, 0, 0, 0},
        {4, 1, 0, 0},
        {9, 2, 0, 0},
        {5, 3, 0, 0}
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
    displayGanttChart(processes, n);

    return 0;
}

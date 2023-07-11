#include <stdio.h>

struct Process {
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0;

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].burstTime + processes[i - 1].waitingTime - processes[i].arrivalTime;

        if (processes[i].waitingTime < 0) {
            processes[i].waitingTime = 0;
        }
    }
}

void calculateTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
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

    for (int i = 0; i < n; i++) {
        printf("%d  ", currentTime);
        currentTime += processes[i].burstTime;
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
    calculateAverageTimes(processes, n);
    displayGanttChart(processes, n);

    return 0;
}

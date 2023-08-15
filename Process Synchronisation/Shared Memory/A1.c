#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MAX_NUMBERS 100
int main()
{
    key_t key = ftok("inpfile", 65); // Unique key for shared memory segment
    int shmid = shmget(key, MAX_NUMBERS * sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    int *sharedArray = (int *)shmat(shmid, NULL, 0);
    if (sharedArray == (int *)-1)
    {
        perror("shmat");
        exit(1);
    }
    FILE *file = fopen("inpfile", "r");
    if (file == NULL)
    {
        perror("fopen");
        exit(1);
    }
    int num;
    int count = 0;
    while (fscanf(file, "%d", &num) == 1 && count < MAX_NUMBERS)
    {
        sharedArray[count] = num;
        count++;
    }
    fclose(file);
    sleep(5);           // Delay B.c start
    shmdt(sharedArray); // Detach shared memory segment
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAX_NUMBERS 100
void sortArray(int *array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
int main()
{
    key_t key = ftok("inpfile", 65); // Same unique key used by A.c
    int shmid = shmget(key, MAX_NUMBERS * sizeof(int), 0666);
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
    // Determine the number of integers in the shared array
    int count = 0;
    while (sharedArray[count] != 0 && count < MAX_NUMBERS)
    {
        count++;
    }
    // Sort the array
    sortArray(sharedArray, count);
    FILE *file = fopen("outfile", "w");
    if (file == NULL)
    {
        perror("fopen");
        exit(1);
    }
    // Write the sorted array to the file
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d ", sharedArray[i]);
    }
    fclose(file);
    shmdt(sharedArray);         // Detach shared memory segment
    shmctl(shmid, IPC_RMID, 0); // Delete shared memory segment
    return 0;
}
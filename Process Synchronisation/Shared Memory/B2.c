#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define MAX_INTS 100
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int shmid;
    int *sharedArray;
    int *done;
    // Create shared memory segment for sharedArray
    key_t key_array = ftok("inpfile", 65);
    shmid = shmget(key_array, MAX_INTS * sizeof(int), S_IRUSR | S_IWUSR);
    sharedArray = (int *)shmat(shmid, NULL, 0);
    // Create shared memory segment for done
    key_t key_done = ftok("donefile", 65);
    int done_shmid = shmget(key_done, sizeof(int), S_IRUSR | S_IWUSR);
    done = (int *)shmat(done_shmid, NULL, 0);
    // Wait until done is set to 1 by A.c
    while (*done != 1)
    {
        // Sleep for a short duration to avoid busy-waiting
        usleep(1000);
    }
    // Determine the number of integers in the shared array
    int numIntegers = 0;
    while (numIntegers < MAX_INTS && sharedArray[numIntegers] != 0)
    {
        numIntegers++;
    }
    // Sort the array
    bubbleSort(sharedArray, numIntegers);
    // Write the sorted array to outfile
    FILE *file = fopen("outfile", "w");
    if (file == NULL)
    {
        printf("Failed to open outfile.\n");
        exit(1);
    }
    for (int i = 0; i < numIntegers; i++)
    {
        fprintf(file, "%d\n", sharedArray[i]);
    }
    fclose(file);
    // Detach shared memory segments
    shmdt(sharedArray);
    shmdt(done);
    return 0;
}
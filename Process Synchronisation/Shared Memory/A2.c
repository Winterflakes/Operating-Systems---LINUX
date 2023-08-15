#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <time.h>
#define MAX_INTS 100
int main()
{
    int shmid;
    int *sharedArray;
    int *done;
    // Create shared memory segment for sharedArray
    key_t key_array = ftok("inpfile", 65);
    shmid = shmget(key_array, MAX_INTS * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    sharedArray = (int *)shmat(shmid, NULL, 0);
    // Create shared memory segment for done
    key_t key_done = ftok("donefile", 65);
    int done_shmid = shmget(key_done, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    done = (int *)shmat(done_shmid, NULL, 0);
    *done = 0;
    // Read integers from inpfile and write them to shared array
    FILE *file = fopen("inpfile", "r");
    if (file == NULL)
    {
        printf("Failed to open inpfile.\n");
        exit(1);
    }
    int numIntegers = 0;
    while (fscanf(file, "%d", &sharedArray[numIntegers]) != EOF)
    {
        numIntegers++;
        if (numIntegers >= MAX_INTS)
        {
            break;
        }
    }
    fclose(file);
    // Set done to 1 to indicate A.c has finished writing
    *done = 1;
    // Wait for a few seconds to simulate delay
    sleep(3);
    // Detach and delete shared memory segments
    shmdt(sharedArray);
    shmdt(done);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(done_shmid, IPC_RMID, NULL);
    return 0;
}
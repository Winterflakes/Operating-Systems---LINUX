#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_KEY 12345
#define ARRAY_SIZE 10

typedef struct
{
    int max;
    int min;
} SharedData;

int main()
{
    int array[ARRAY_SIZE] = {5, 2, 7, 9, 1, 3, 6, 8, 4, 0};

    int shmid = shmget(SHM_KEY, sizeof(SharedData), IPC_CREAT | 0666);

    SharedData *shared_data = (SharedData *)shmat(shmid, NULL, 0);

    shared_data->max = shared_data->min = array[0];
    for (int i = 1; i < ARRAY_SIZE; i++)
    {
        if (array[i] > shared_data->max)
        {
            shared_data->max = array[i];
        }
        if (
            array[i] <
            shared_data->min)
        {
            shared_data->min = array[i];
        }
    }

    printf("Maximum: %d\n", shared_data->max);
    printf("Minimum: %d\n", shared_data->min);

    shmdt(shared_data);
    
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
#include <stdio.h>
#define MAX_BLOCKS 100
#define MAX_FILES 100

void bestFit(int blockSize[], int m, int fileSize[], int n)
{
    int allocation[MAX_FILES];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= fileSize[i])
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= fileSize[i];
        }
    }
    
    printf("\nFile No.\tFile Size\tBlock No.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, fileSize[i]);
        if (allocation[i] != -1)
        {
            printf("%d\n", allocation[i] + 1);
        }
        else
        {
            printf("Not Allocated\n");
        }
    }
}

int main()
{
    int blockSize[MAX_BLOCKS], fileSize[MAX_FILES];
    int m, n;
    
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    
    printf("Enter the number of files: ");
    scanf("%d", &n);
    
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &blockSize[i]);
    }
    
    printf("Enter the sizes of the files:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &fileSize[i]);
    }
    
    bestFit(blockSize, m, fileSize, n);
    
    return 0;
}

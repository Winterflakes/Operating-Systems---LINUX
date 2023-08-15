#include <stdio.h>
#include <stdlib.h>

void fcfs(int tracks[], int n, int head)
{
    int seek_count = 0;
    
    printf("%d -> ", head);
    
    for (int i = 0; i < n; i++)
    {
        seek_count += abs(tracks[i] - head);
        head = tracks[i];
        printf("%d -> ", head);
    }
    
    printf("\nTotal head movement: %d\n", seek_count);
}

int main()
{
    int n, head;
    printf("Enter the number of tracks: ");
    scanf("%d", &n);
    
    int tracks[n];
    printf("Enter the track positions:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tracks[i]);
    }
    
    printf("Enter the head position: ");
    scanf("%d", &head);
    
    printf("\nHead movement trace:\n");
    fcfs(tracks, n, head);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int abs(int a) {
    return (a < 0) ? -a : a;
}

int findShortestDistance(int tracks[], int n, int head, int visited[]) {
    int min_distance = abs(tracks[0] - head);
    int index = 0;
    
    for (int i = 1; i < n; i++) {
        if (!visited[i]) {
            int distance = abs(tracks[i] - head);
            if (distance < min_distance) {
                min_distance = distance;
                index = i;
            }
        }
    }
    
    return index;
}

void sstf(int tracks[], int n, int head) {
    int seek_count = 0;
    int visited[n];
    
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    
    printf("%d -> ", head);
    
    for (int i = 0; i < n; i++) {
        int shortest_index = findShortestDistance(tracks, n, head, visited);
        visited[shortest_index] = 1;
        
        printf("%d -> ", tracks[shortest_index]);
        seek_count += abs(tracks[shortest_index] - head);
        head = tracks[shortest_index];
    }
    
    printf("\nTotal head movement: %d\n", seek_count);
}

int main() {
    int n, head;
    
    printf("Enter the number of tracks: ");
    scanf("%d", &n);
    
    int tracks[n];
    printf("Enter the track positions:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tracks[i]);
    }
    
    printf("Enter the head position: ");
    scanf("%d", &head);
    
    printf("\nHead movement trace:\n");
    sstf(tracks, n, head);
    
    return 0;
}

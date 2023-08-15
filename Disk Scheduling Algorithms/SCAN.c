#include <stdio.h>
#include <stdlib.h>
// Function to sort an array in ascending order
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
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
void scan(int tracks[], int n, int head, char direction)
{
    // Sort the tracks array in ascending order
    sort(tracks, n);
    int i, j, seek_count = 0;
    int distance, cur_track;
    int left[n], right[n];
    int left_count = 0, right_count = 0;
    // Divide the tracks into two arrays: left and right
    for (i = 0; i < n; i++)
    {
        if (tracks[i] < head)
            left[left_count++] = tracks[i];
        if (tracks[i] > head)
            right[right_count++] = tracks[i];
    }
    // Perform SCAN algorithm based on the direction
    if (direction == 'l')
    {
        for (i = left_count - 1; i >= 0; i--)
        {
            cur_track = left[i];
            printf("%d -> ", cur_track);
            seek_count += abs(cur_track - head);
            head = cur_track;
        }
        printf("0 -> ");
        for (j = 0; j < right_count; j++)
        {
            cur_track = right[j];
            printf("%d -> ", cur_track);
            seek_count += abs(cur_track - head);
            head = cur_track;
        }
    }
    else if (direction == 'r')
    {
        for (j = 0; j < right_count; j++)
        {
            cur_track = right[j];
            printf("%d -> ", cur_track);
            seek_count += abs(cur_track - head);
            head = cur_track;
        }
        printf("199 -> ");
        for (i = left_count - 1; i >= 0; i--)
        {
            cur_track = left[i];
            printf("%d -> ", cur_track);
            seek_count += abs(cur_track - head);
            head = cur_track;
        }
    }
    printf("\nTotal head movement: %d\n", seek_count);
}
int main()
{
    int n, head;
    char direction;
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
    printf("Enter the direction (l for left, r for right): ");
    scanf(" %c", &direction);
    printf("\nHead movement trace:\n");
    scan(tracks, n, head, direction);
    return 0;
}
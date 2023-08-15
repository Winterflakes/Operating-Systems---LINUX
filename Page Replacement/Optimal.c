#include <stdio.h>
#define MAX_FRAMES 10
#define INF 999999

int main()
{
    int frames[MAX_FRAMES], faults = 0;
    int num_frames, num_pages;
    
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);
    
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);
    
    int pages[num_pages];
    
    printf("Enter the page reference string:\n");
    for (int i = 0; i < num_pages; i++)
    {
        scanf("%d", &pages[i]);
    }
    
    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = -1;
    }
    
    for (int i = 0; i < num_pages; i++)
    {
        int page = pages[i];
        int found = 0;
        
        // Check if the page is already in a frame
        for (int j = 0; j < num_frames; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }
        
        if (!found)
        {
            int victimIdx = -1;
            int farthest = -1;
            
            // Find the frame that will not be used for the longest time
            for (int j = 0; j < num_frames; j++)
            {
                int k;
                for (k = i + 1; k < num_pages; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        break;
                    }
                }
                if (k == num_pages)
                {
                    victimIdx = j;
                    break;
                }
                if (k > farthest)
                {
                    farthest = k;
                    victimIdx = j;
                }
            }
            
            if (victimIdx != -1)
            {
                frames[victimIdx] = page;
                faults++;
            }
        }
        
        printf("Page reference: %d - Frames: ", page);
        for (int j = 0; j < num_frames; j++)
        {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    
    printf("Total page faults: %d\n", faults);
    return 0;
}

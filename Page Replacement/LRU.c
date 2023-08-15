#include <stdio.h>
#define MAX_FRAMES 10

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
                // Move the current page to the most recently used position
                for (int k = j; k > 0; k--)
                {
                    frames[k] = frames[k - 1];
                }
                frames[0] = page;
                break;
            }
        }
        
        if (!found)
        {
            // Replace the least recently used page with the current page
            for (int j = num_frames - 1; j > 0; j--)
            {
                frames[j] = frames[j - 1];
            }
            frames[0] = page;
            faults++;
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

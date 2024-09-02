#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

void fifo(int referenceString[], int n, int capacity);
void optimal(int referenceString[], int n, int capacity);
void lru(int referenceString[], int n, int capacity);

int main() 
{
    int n, i, referenceString[MAX_PAGES], capacity;

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &referenceString[i]);

    printf("Enter the capacity of the memory: ");
    scanf("%d", &capacity);

    fifo(referenceString, n, capacity);
    optimal(referenceString, n, capacity);
    lru(referenceString, n, capacity);

    return 0;
}

void fifo(int referenceString[], int n, int capacity)
{
    int frames[MAX_FRAMES] = {0};
    int pageFaults = 0;
    int frameIndex = 0;
    int i, j;

    printf("\nFIFO Page Replacement\n");

    for (i = 0; i < n; i++)
    {
        int pageExists = 0;
        for (j = 0; j < capacity; j++)
        {
            if (frames[j] == referenceString[i])
            {
                pageExists = 1;
                break;
            }
        }

        if (!pageExists)
        {
            frames[frameIndex] = referenceString[i];
            frameIndex = (frameIndex + 1) % capacity;
            pageFaults++;
        }
    }

    printf("Number of page faults: %d\n", pageFaults);
}

void optimal(int referenceString[], int n, int capacity)
{
    int frames[MAX_FRAMES] = {0};
    int pageFaults = 0;
    int i, j;

    printf("\nOptimal Page Replacement\n");

    for (i = 0; i < n; i++)
    {
        int pageExists = 0;
        for (j = 0; j < capacity; j++)
        {
            if (frames[j] == referenceString[i])
            {
                pageExists = 1;
                break;
            }
        }

        if (!pageExists)
        {
            int k, l, index = -1, farthest = i;
            for (k = 0; k < capacity; k++)
            {
                for (l = i + 1; l < n; l++)
                {
                    if (frames[k] == referenceString[l])
                    {
                        if (l > farthest)
                        {
                            farthest = l;
                            index = k;
                        }
                        break;
                    }
                }
                if (l == n)
                {
                    index = k;
                    break;
                }
            }

            if (index != -1)
            {
                frames[index] = referenceString[i];
                pageFaults++;
            }
        }
    }

    printf("Number of page faults: %d\n", pageFaults);
}

void lru(int referenceString[], int n, int capacity)
{
    int frames[MAX_FRAMES] = {0};
    int pageFaults = 0;
    int recent[MAX_FRAMES] = {0};
    int i, j;

    printf("\nLRU Page Replacement\n");

    for (i = 0; i < n; i++)
    {
        int pageExists = 0;
        for (j = 0; j < capacity; j++)
        {
            if (frames[j] == referenceString[i])
            {
                pageExists = 1;
                recent[j] = i;
                break;
            }
        }

        if (!pageExists)
        {
            int k, index = 0, oldest = recent[0];
            for (k = 1; k < capacity; k++)
            {
                if (recent[k] < oldest)
                {
                    oldest = recent[k];
                    index = k;
                }
            }

            frames[index] = referenceString[i];
            recent[index] = i;
            pageFaults++;
        }
    }

    printf("Number of page faults: %d\n", pageFaults);
}

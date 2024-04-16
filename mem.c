#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);
void calculateFragmentation(int blockSize[], int m, int processSize[], int n, char *strategy);

int main() 
{
   int m, n, i;
   int blockSize[MAX_BLOCKS], processSize[MAX_BLOCKS];
   
   printf("Enter the number of memory blocks: ");
   scanf("%d", &m);

   printf("Enter the size of each memory block: ");
   for(i = 0; i < m; i++)
       scanf("%d", &blockSize[i]);

   printf("Enter the number of processes: ");
   scanf("%d", &n);

   printf("Enter the size of each process: ");
   for(i = 0; i < n; i++)
       scanf("%d", &processSize[i]);
   
   firstFit(blockSize, m, processSize, n);
   bestFit(blockSize, m, processSize, n);
   worstFit(blockSize, m, processSize, n);

   return 0;
}

void firstFit(int blockSize[], int m, int processSize[], int n) 
{
   printf("\nFirst Fit Allocation\n");
   calculateFragmentation(blockSize, m, processSize, n, "First Fit");
}

void bestFit(int blockSize[], int m, int processSize[], int n) 
{
   printf("\nBest Fit Allocation\n");
   calculateFragmentation(blockSize, m, processSize, n, "Best Fit");
}

void worstFit(int blockSize[], int m, int processSize[], int n) 
{
   printf("\nWorst Fit Allocation\n");
   calculateFragmentation(blockSize, m, processSize, n, "Worst Fit");
}

void calculateFragmentation(int blockSize[], int m, int processSize[], int n, char *strategy) 
{
   int allocation[MAX_BLOCKS], i, j, externalFragmentation = 0, internalFragmentation = 0;
   int blockAllocated[MAX_BLOCKS][MAX_BLOCKS] = {{0}};

   for(i = 0; i < n; i++) {
       allocation[i] = -1;
   }

   for(i = 0; i < n; i++) {
       for(j = 0; j < m; j++) {
           if(blockSize[j] >= processSize[i]) {
               allocation[i] = j;
               blockSize[j] -= processSize[i];
               blockAllocated[j][i] = 1;
               break;
           }
       }
   }

   printf("Process No.\tProcess Size\tBlock no.\n");
   for(i = 0; i < n; i++) {
       printf("%d\t\t%d\t\t", i+1, processSize[i]);
       if(allocation[i] != -1) {
           printf("%d\n", allocation[i] + 1);
       } else {
           printf("Not Allocated\n");
           externalFragmentation += processSize[i];
       }
   }

   for(i = 0; i < m; i++) {
       internalFragmentation += blockSize[i];
   }

   printf("\n%s Fragmentation:\n", strategy);
   printf("Internal Fragmentation: %d\n", internalFragmentation);
   printf("External Fragmentation: %d\n", externalFragmentation);

   printf("\nBlocks with Processes:\n");
   for(i = 0; i < m; i++) {
       printf("Block %d: ", i+1);
       for(j = 0; j < n; j++) {
           if(blockAllocated[i][j])
               printf("%d ", j+1);
       }
       printf("\n");
   }
}

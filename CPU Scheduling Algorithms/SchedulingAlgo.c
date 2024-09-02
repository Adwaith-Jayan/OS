/* To implement scheduling algorithms */
#include <stdio.h>
#include <string.h>

int n;
struct ProcessInfo
{
   char PID[5];
   int arrival_time;
   int burst_time;
   int priority;
};
struct ProcessInfo P[10];

struct Table
{
   char PID[5];
   int arrival_time;
   int burst_time;
   int completion_time;
   int response_time;
   int turnaround_time;
   int waiting_time;
};
void display(struct Table table[])
{
   printf("PID\tArrival Time\tBurst Time\tCompletion Time\tRespone Time\tTurn Around Time\tWaiting Time\n");
   for(int i=0;i<n;i++)
   {
      printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",table[i].PID,table[i].arrival_time,table[i].burst_time,table[i].completion_time,table[i].response_time,
      table[i].turnaround_time,table[i].waiting_time);
   }
}
void FCFS()
{
   int systime=0;
   struct Table fcfs[n];
   for(int i=0;i<n;i++)
   {
      if(P[i].arrival_time <= systime)
      {
         strcpy(fcfs[i].PID,P[i].PID);
         fcfs[i].arrival_time=P[i].arrival_time;
         fcfs[i].burst_time=P[i].burst_time;
         fcfs[i].completion_time=systime+P[i].burst_time;
         fcfs[i].response_time=systime-fcfs[i].arrival_time;
         fcfs[i].turnaround_time=fcfs[i].completion_time - fcfs[i].arrival_time;
       	 fcfs[i].waiting_time=fcfs[i].turnaround_time - fcfs[i].burst_time;
         systime+=P[i].burst_time;
      }
   }
   printf("\tFIRST COME FIRST SERVE ALGORITHM\n");
   display(fcfs);

}

void swap(struct ProcessInfo *a, struct ProcessInfo *b)
{
   struct ProcessInfo temp = *a;
   *a = *b;
   *b = temp;
}
void sort_SJF(struct ProcessInfo a[])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j].burst_time > a[j + 1].burst_time && a[j].arrival_time!=0)
            {
                swap(&a[j],&a[j+1]);
            }
        }
    }
}

void SJF()
{
   int systime=0;
   struct Table sjf[n];
   struct ProcessInfo sorted_sjf[n];
   for(int i=0;i<n;i++)
   {
      strcpy(sorted_sjf[i].PID,P[i].PID);
      sorted_sjf[i].arrival_time=P[i].arrival_time;
      sorted_sjf[i].burst_time=P[i].burst_time;
   }
   sort_SJF(sorted_sjf);
   for(int i=0;i<n;i++)
    {
       printf("\n\n\n%s\t",sjf[i].PID);
       printf("%d\t",sjf[i].arrival_time);
       printf("%d\n\n\n",sjf[i].burst_time);
    }

   for(int i=0;i<n;i++)
   {
      if(sorted_sjf[i].arrival_time <= systime)
      {
         strcpy(sjf[i].PID,sorted_sjf[i].PID);
         sjf[i].arrival_time=sorted_sjf[i].arrival_time;
         sjf[i].burst_time=sorted_sjf[i].burst_time;
         sjf[i].completion_time=systime + sorted_sjf[i].burst_time;
         sjf[i].response_time=systime - sjf[i].arrival_time;
         sjf[i].turnaround_time=sjf[i].completion_time - sjf[i].arrival_time;
       	 sjf[i].waiting_time=sjf[i].turnaround_time - sjf[i].burst_time;
         systime+=sjf[i].burst_time;
      }
   }
   printf("\n\n\t SJF\n");
   display(sjf);
}

void sort_priority(struct ProcessInfo a[])
{
   for(int i=0;i<n;i++)
   {
       for(int j=0;j<n-i-1;j++)
       {
          if(a[j].priority < a[j+1].priority && a[j].arrival_time!=0)
          {
             swap(&a[j],&a[j+1]);
          }
       }
   }
}
void Priority_Scheduling()
{
   int systime=0;
   struct Table priorityTable[n];
   struct ProcessInfo sorted_priority[n];
   for(int i=0;i<n;i++)
   {
      strcpy(sorted_priority[i].PID,P[i].PID);
      sorted_priority[i].arrival_time=P[i].arrival_time;
      sorted_priority[i].burst_time=P[i].burst_time;
      sorted_priority[i].priority=P[i].priority;
   }
   sort_priority(sorted_priority);
   for(int i=0;i<n;i++)
   {
      if(sorted_priority[i].arrival_time <= systime)
      {
         strcpy(priorityTable[i].PID,sorted_priority[i].PID);
         priorityTable[i].arrival_time=sorted_priority[i].arrival_time;
         priorityTable[i].burst_time=sorted_priority[i].burst_time;
         priorityTable[i].completion_time=systime + sorted_priority[i].burst_time;
         priorityTable[i].response_time=systime - priorityTable[i].arrival_time;
         priorityTable[i].turnaround_time=priorityTable[i].completion_time - priorityTable[i].arrival_time;
         priorityTable[i].waiting_time=priorityTable[i].turnaround_time - priorityTable[i].burst_time;
         systime+=sorted_priority[i].burst_time;
      }
   }
   printf("\n\n\t Priority Scheduling\n");
   display(priorityTable);
}

void RoundRobin()
{
    int remaining = n;
    int systime = 0;
    struct Table rr[n];

    for (int i = 0; i < n; i++)
   {
        strcpy(rr[i].PID, P[i].PID);
        rr[i].arrival_time = P[i].arrival_time;
        rr[i].burst_time = P[i].burst_time;
        rr[i].response_time=-1;
    }

    while (remaining > 0) {
        for (int i = 0; i < n; i++) {
            if (rr[i].burst_time > 0) {
                int quantum = 1;
                if(rr[i].response_time==-1)
                {
                   rr[i].response_time=systime - rr[i].arrival_time;
                }
                rr[i].burst_time -= quantum;
                systime += quantum;
                if (rr[i].burst_time <= 0) {
                    rr[i].completion_time = systime;
                    rr[i].turnaround_time = rr[i].completion_time - rr[i].arrival_time;
                    rr[i].waiting_time = rr[i].completion_time - P[i].burst_time;
                    remaining--;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        rr[i].burst_time = P[i].burst_time;
    }

    printf("\n\n\t Round Robin\n");
    display(rr);
}

void main()
{
   printf("How many process? ");
   scanf("%d",&n);
   printf("Enter details of Process\n");
   printf("PID\tArrival Time\tBurst Time\tPriority\n");
   for(int i=0;i<n;i++)
   {
      scanf(" %s",P[i].PID);
      scanf("%d",&P[i].arrival_time);
      scanf("%d",&P[i].burst_time);
      scanf("%d",&P[i].priority);
   }
   FCFS();
   SJF();
   Priority_Scheduling();
   RoundRobin();
}

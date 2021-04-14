#include <stdio.h>
#include<stdlib.h>

typedef struct Process{
    char id;
    int arrivalTime;
    int burstTime;
    int startTime;
    int pendingBurstTime;
    int waitTime;
    int turnAroundTime;
    int priority;
}Process;

Process * newProcess(char ID, int AT, int BT, int priority)
{
    Process *temp = (Process *)malloc(sizeof(Process));
    temp -> id = ID;
    temp -> arrivalTime = AT;
    temp -> burstTime = BT;
    temp -> pendingBurstTime = BT;
    temp -> waitTime = 0;
    temp -> turnAroundTime = 0;
    temp -> priority = priority;
    return temp;
}

void swap(Process * a, Process * b)

{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortByArrival(Process *p[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (p[j] -> arrivalTime < p[min_idx] -> arrivalTime)
                min_idx = j;

        swap(p[min_idx], p[i]);
    }
}

void runFCFS(Process *p[],int n){
    int totalWait = 0, totalTurnAround = 0;
    int time = 0;
    sortByArrival(p, n);
    for (int i = 0; i < n; i++){

        if (time < p[i] -> arrivalTime){
            time = p[i] -> arrivalTime;
        }
        p[i] -> waitTime = time - p[i] -> arrivalTime;
        p[i] -> turnAroundTime = p[i] -> waitTime + p[i] -> burstTime;
        printf("\nProcess %c",p[i] -> id);
        printf("\nArrival Time: %d",p[i] -> arrivalTime);
        printf("\nBurst Time: %d",p[i] -> burstTime);
        printf("\nWaiting Time: %d",p[i] -> waitTime);
        printf("\nTurn Around Time: %d",p[i] -> turnAroundTime);
        printf("\nCompletion Time: %d\n", p[i]->arrivalTime + p[i] -> turnAroundTime );
        time = p[i]->arrivalTime + p[i] -> turnAroundTime;
        totalWait += p[i] -> waitTime;
        totalTurnAround += p[i] -> turnAroundTime;
    }

    printf("\nAverage Waiting Time: %d", totalWait / n);
    printf("\nAverage Turn Around Time: %d\n", totalTurnAround / n);
}

void sortByBurst(Process *p[], int n)

{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (p[j] -> burstTime < p[min_idx] -> burstTime)
                min_idx = j;

        swap(p[min_idx], p[i]);
    }
}

void runSJF(Process *p[], int n){
    int time = 0, totalWait = 0, totalTurnAround = 0;
    sortByArrival(p,n);
    int completed = 0, select;
    do{
        select = 0;
        for(int i = completed; i < n; i++){
            if(time >= p[i] -> arrivalTime){
                select++;
                continue;
            }else{
                break;
            }
        }
        sortByBurst(&p[completed], select);

        int current = completed;
        if(time < p[current] -> arrivalTime)
            time = p[current] -> arrivalTime;
        p[current] -> waitTime = time - p[current] -> arrivalTime;
        p[current] -> turnAroundTime = p[current] -> waitTime + p[current] -> burstTime;
        printf("\nProcess %c",p[current] -> id);
        printf("\nArrival Time: %d",p[current] -> arrivalTime);
        printf("\nBurst Time: %d",p[current] -> burstTime);
        printf("\nWaiting Time: %d",p[current] -> waitTime);
        printf("\nTurn Around Time: %d",p[current] -> turnAroundTime);
        printf("\nCompletion Time: %d\n", p[current] -> arrivalTime + p[current] -> turnAroundTime );
        time = p[current] -> arrivalTime + p[current] -> turnAroundTime;
        totalWait += p[current] -> waitTime;
        totalTurnAround += p[current] -> turnAroundTime;

        completed ++;
    }while (completed < n);

    printf("\nAverage Waiting Time: %d", totalWait / n);
    printf("\nAverage Turn Around Time: %d\n", totalTurnAround / n);
    printf("\nTime Spent: %d", time);
    
}

void prioritySort(Process *p[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (p[j] -> priority > p[min_idx] -> priority)
                min_idx = j;

        swap(p[min_idx], p[i]);
    }
}

void runPriorityScheduling(Process *p[],int n){
    int time = 0, totalWait = 0, totalTurnAround = 0;
    sortByArrival(p,n);
    int completed = 0, select;
    do{
        select = 0;
        for(int i = completed; i < n; i++){
            if(time >= p[i] -> arrivalTime){
                select++;
                continue;
            }else{
                break;
            }
        }

        prioritySort(&p[completed], select);

        int current = completed;
        if(time < p[current] -> arrivalTime)
            time = p[current] -> arrivalTime;
        p[current] -> waitTime = time - p[current] -> arrivalTime;
        p[current] -> turnAroundTime = p[current] -> waitTime + p[current] -> burstTime;
        printf("\nProcess %c",p[current] -> id);
        printf("\nPriority: %d",p[current] -> priority);
        printf("\nArrival Time: %d",p[current] -> arrivalTime);
        printf("\nBurst Time: %d",p[current] -> burstTime);
        printf("\nWaiting Time: %d",p[current] -> waitTime);
        printf("\nTurn Around Time: %d",p[current] -> turnAroundTime);
        printf("\nCompletion Time: %d\n", p[current] -> arrivalTime + p[current] -> turnAroundTime );
        time = p[current] -> arrivalTime + p[current] -> turnAroundTime;
        totalWait += p[current] -> waitTime;
        totalTurnAround += p[current] -> turnAroundTime;

        completed ++;
    }while (completed < n);

    printf("\nAverage Waiting Time: %d", totalWait / n);
    printf("\nAverage Turn Around Time: %d\n", totalTurnAround / n);
    printf("\nTime Spent: %d", time);
}

void runRoundRobin(Process *p[], int n, int timeQuantum){
    int time = 0, totalWait = 0, totalTurnAround = 0, completed = 0, select;
    sortByArrival(p,n);
    time = p[0] -> arrivalTime;
    do{
    for (int i = 0; i < n; i++){

        if (time >= p[i] -> arrivalTime){
            if (p[i] -> pendingBurstTime == p[i] -> burstTime)
                p[i] -> startTime = time;

            if (p[i] -> pendingBurstTime <= 0){
                continue;
            }else if(p[i] -> pendingBurstTime <= timeQuantum){
                time += p[i] -> pendingBurstTime;
                
                p[i] -> pendingBurstTime = 0;
                p[i] -> turnAroundTime = time - p[i] -> arrivalTime;
                p[i] -> waitTime = p[i] -> turnAroundTime - p[i] -> burstTime;
                totalWait += p[i] -> waitTime;
                totalTurnAround += p[i] -> turnAroundTime;
                
                printf("\nProcess %c", p[i] -> id);
                printf("\nArrival Time: %d", p[i] -> arrivalTime);
                printf("\nBurst Time: %d", p[i] -> burstTime);
                printf("\nStart Time: %d", p[i] -> startTime);
                printf("\nWaiting Time: %d", p[i] -> waitTime);
                printf("\nTurn Around Time: %d", p[i] -> turnAroundTime);
                printf("\nCompletion Time: %d\n", p[i] -> arrivalTime +  p[i] -> turnAroundTime );

                completed ++;
                if(completed >= n)
                    break;
            }else{
                p[i] -> pendingBurstTime -= timeQuantum;
                time += timeQuantum;
                continue;
            }
        }
    }
    }while(completed < n);

    printf("\nAverage Waiting Time: %d", totalWait / n);
    printf("\nAverage Turn Around Time: %d\n", totalTurnAround / n);
    printf("\nTime Spent: %d", time);
}


int main(){
    // int n = 10;
    // Process * p[n];

    // // p[0] = newProcess (65, 2, 3, 5);
    // // p[1] = newProcess (66, 0, 4, 9);
    // // p[2] = newProcess (67, 4, 2, 1);
    // // p[3] = newProcess (68, 5, 4, 6);
    // // p[4] = newProcess (70, 3, 2, 0);
    // // p[5] = newProcess (71, 3, 2, 5);
    // // p[6] = newProcess (72, 3, 2, 3);
    // // p[7] = newProcess (73, 3, 2, 2);
    // // p[8] = newProcess (74, 3, 2, 1);
    // // p[9] = newProcess (75, 3, 2, 7);

    // runRoundRobin(p, 5, 3);

    int choice , n;
    int id, arrivalTime, burstTime, timeQuantum, priority;

    do{
        printf("Enter the number of processes: \n");
        scanf("%d", &n);
        Process *p[n];
        for(int i=0; i<n; i++){
            printf("\nEnter the arrival time for process %c: ", 64+i);
            scanf("%d", &arrivalTime);
            printf("\nEnter the burst time for process %c: \n", 64+i);
            scanf("%d", &burstTime);
            p[i] = newProcess(64+i, arrivalTime, burstTime, 0);
        }
        printf("\n1)First Come First Serve");
        printf("\n2)Shortest Job First");
        printf("\n3)Priority Scheduling");
        printf("\n4)Round Robin\n");
        printf("\nChoose an algorithm");
        
        switch (choice)
        {
        case 1:
            runFCFS(p, n);
            break;

        case 2:
            runSJF(p, n);
            break;
        case 3:
            for(int i=0; i<n; i++){
                printf("\nEnter the priority for process %c: ", 64+i);
                scanf("%d", &priority);
                p[i] -> priority = priority;
            }
            runPriorityScheduling(p, n);
            break;
        case 4:
            printf("\nEnter the time slice value: ");
            scanf("%d", &timeQuantum);
            runRoundRobin(p, n, timeQuantum);
            break;
        
        default:
            break;
        
        }
        printf("Enter 0 to exit or any other number to continue.....");
    }while(choice != 0);
    
}



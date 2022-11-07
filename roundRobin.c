#include <stdio.h>
#include <stdlib.h>
//---------------------

int cpuData[50][700];
char *File_Name = "CPULoad.dat";
int NoOfProcess = 0;

void arrayManager() {

    FILE *fp;
    int data = 0;
    fp = fopen(File_Name, "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    while (!feof(fp)) {
        char ch = fgetc(fp);
        if (ch == '\n') {
            NoOfProcess++;
            data = 0;
        } else if (ch == ' ') {
            data++;
            cpuData[NoOfProcess][data] = 0;
        } else {
            if (ch == '(' || ch == ')') {
            } else {
                cpuData[NoOfProcess][data] =
                        (cpuData[NoOfProcess][data] * 10) + (ch - '0');
            }
        }
    }
    printf("Total number of Process: %d\n", NoOfProcess);
    //    printf("Data in 8th NoOfProcess is: %d\n", cpuData[25][0]);
}

int getArrivalTime(int i) {
    if (i >= 0 && i < NoOfProcess) {
        return cpuData[i][1];
    }
    printf("Error in getArrivalTime");
}

int getBurstTime(int i) {
    if (i >= 0 && i < NoOfProcess) {
        return cpuData[i][2];
    }
    printf("Error in getBurstTime");
}

//---------------------
int main() {
    arrayManager();
    int i, limit, total = 0, x, counter = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, arrival_time[NoOfProcess],
            burst_time[NoOfProcess], temp[NoOfProcess];
    float average_wait_time = 0, average_turnaround_time = 0;
    //    printf("nEnter Number of Processes:");
    //    scanf("%d", &limit);
    limit = NoOfProcess;
    x = limit;
    for (i = 0; i < limit; i++) {
        //        printf("Process name %d\t", i + 1);

        //        printf("Arrival Time:");
        //
        //        scanf("%d", &arrival_time[i]);
        arrival_time[i] = getArrivalTime(i);

        //        printf("Burst Time:");
        //
        //        scanf("%d", &burst_time[i]);
        burst_time[i] = getBurstTime(i);

        temp[i] = burst_time[i];
    }
    int finishedProcess = 0;
    printf("Enter Time Quantum(MAX TIME FOR EACH PROCESS)");
    scanf("%d", &time_quantum);
    //    for (int j_=0;j_<=NoOfProcess;j_++){
    //        printf("Process[%d] Arrival Time: %d\tBurst Time:
    //        %d\n",j_,arrival_time[j_],burst_time[j_]);
    //    }
    printf("Process ID\tBurst Time Turnaround Time Waiting Time\n");
    for (int i = 0; finishedProcess < (NoOfProcess - 1); i++) {
        if (i == (NoOfProcess - 1) && finishedProcess != (NoOfProcess - 1)) {
            //            printf("\nCPU is idle for 1 unit\n");
            //            printf("##");
            average_turnaround_time += time_quantum;
            i = 0;
        }
        if (temp[i] <= time_quantum && temp[i] > 0) {
            temp[i] -= time_quantum;
            if (temp[i] <= 0) {
                //                printf("Process %d finished\t", i);
                printf("%d\t\t%d\t\t%d\t\t%d\n", i, burst_time[i],
                       (time_quantum + temp[i]),
                       (time_quantum + temp[i] - burst_time[i]));
                finishedProcess++;
            } else {
                average_wait_time += time_quantum;
            }

        } else if (temp[i] > 0) {
            temp[i] -= time_quantum;
            if (temp[i] <= 0) {
                //                printf("Process %d finished\t", i);
                printf("%d\t\t%d\t\t%d\t\t%d\n", i, burst_time[i],
                       (time_quantum + temp[i]),
                       (time_quantum + temp[i] - burst_time[i]));
                finishedProcess++;
            } else {
                average_wait_time += time_quantum;
            }
        }
    }

    //    average_wait_time = wait_time * 1.0 / limit;
    //    average_turnaround_time = turnaround_time * 1.0 / limit;
    printf("\nAverage Waiting Time:%f", average_wait_time / NoOfProcess);
    printf("\nAvg Turnaround Time:%f", average_turnaround_time / NoOfProcess);
    return 0;
}
#include <stdio.h>

int main() {
    int A[100][4]; // Array to store process details: Process ID, Burst Time, Waiting Time, Turnaround Time
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]); // Taking burst time input for each process
        A[i][0] = i + 1; // Storing process ID
    }

    // Sorting processes based on burst time (FCFS)
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++)
            if (A[j][1] < A[index][1])
                index = j;

        // Swapping burst time and process ID
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    // Calculating waiting and turnaround times
    A[0][2] = 0; // First process has 0 waiting time
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++)
            A[i][2] += A[j][1]; // Waiting time is sum of burst times of previous processes
        total += A[i][2];
    }

    // Printing process details and calculating total turnaround time
    printf("Process  Burst Time  Waiting Time  Turnaround Time\n");
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2]; // Turnaround time = Burst Time + Waiting Time
        total += A[i][3];
        printf("P%d       %d            %d             %d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    // Calculating average waiting and turnaround times
    avg_wt = (float)total / n;
    avg_tat = (float)total / n;

    printf("Average Waiting Time = %f\n", avg_wt);
    printf("Average Turnaround Time = %f\n", avg_tat);

    return 0;
}

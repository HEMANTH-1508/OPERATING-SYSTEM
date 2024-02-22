#include <stdio.h>

#define MAX_PROCESS 10

// Structure to represent a process
struct Process {
    int id;             // Process ID
    int burst_time;     // Burst time of the process
    int remaining_time; // Remaining burst time of the process
};

int main() 
{
    int n, quantum, i, total_burst_time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESS];

    // Input details for each process
    for (i = 0; i < n; i++) 
    {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        total_burst_time += processes[i].burst_time;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    printf("\nGantt Chart:\n");
    int current_time = 0;
    while (completed < n) 
    {
        for (i = 0; i < n; i++) 
        {
            if (processes[i].remaining_time > 0) 
            {
                // Execute the process for the time quantum or its remaining time, whichever is smaller
                int execute_time = (processes[i].remaining_time < quantum) ? processes[i].remaining_time : quantum;
                printf("P%d ", processes[i].id);
                current_time += execute_time;
                processes[i].remaining_time -= execute_time;

                if (processes[i].remaining_time == 0) 
                {
                    completed++;
                }
            }
        }
    }
    printf("\n");

    return 0;
}

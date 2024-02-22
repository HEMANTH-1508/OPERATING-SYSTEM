#include <stdio.h>

// Structure to represent a process
struct Process 
{
    int id;             // Process ID
    int burst_time;     // Burst time of the process
    int priority;       // Priority of the process (lower value indicates higher priority)
    int executed;       // Flag to track if process has been executed
};

int main() 
{
    int n, i, total_burst_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input details for each process
    for (i = 0; i < n; i++) 
    {
        printf("Enter burst time and priority for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].priority);
        processes[i].id = i + 1;
        processes[i].executed = 0;
        total_burst_time += processes[i].burst_time;
    }

    int current_time = 0;
    printf("\nGantt Chart:\n");
    while (current_time < total_burst_time) 
    {
        int highest_priority = -1;
        int highest_priority_idx = -1;

        // Find the process with the highest priority
        for (i = 0; i < n; i++) 
        {
            if (processes[i].burst_time > 0 && processes[i].priority > highest_priority && processes[i].executed == 0) 
            {
                highest_priority = processes[i].priority;
                highest_priority_idx = i;
            }
        }

        if (highest_priority_idx == -1) 
        {
            printf("CPU idle at time %d\n", current_time);
            current_time++;
        } 
        else 
        {
            // Execute the process with the highest priority
            printf("P%d ", processes[highest_priority_idx].id);
            processes[highest_priority_idx].burst_time--;
            current_time++;

            // Mark the process as executed if it has completed
            if (processes[highest_priority_idx].burst_time == 0) 
            {
                processes[highest_priority_idx].executed = 1;
            }
        }
    }
    printf("\n");

    return 0;
}

#include <stdio.h>
#define MAX_PROCESS 10
#define TIME_QUANTUM 2

void nonPreemptivePriorityScheduling(int arrival_time[], int burst_time[], int priority[], int n) {
    int waiting_time[MAX_PROCESS], turnaround_time[MAX_PROCESS], completion_time[MAX_PROCESS];
    float total_waiting_time = 0, total_turnaround_time = 0;


    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                int temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;

                temp = arrival_time[j];
                arrival_time[j] = arrival_time[j + 1];
                arrival_time[j + 1] = temp;

                temp = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp;
            }
        }
    }

    completion_time[0] = burst_time[0];
    waiting_time[0] = 0;
    turnaround_time[0] = completion_time[0] - arrival_time[0];

    for (int i = 1; i < n; i++) {
        completion_time[i] = completion_time[i - 1] + burst_time[i];
        waiting_time[i] = completion_time[i - 1] - arrival_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\t\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t\t%d\t\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], priority[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

void preemptivePriorityScheduling(int arrival_time[], int burst_time[], int priority[], int n) {
    int remaining_time[MAX_PROCESS];
    int completion_time[MAX_PROCESS];
    int waiting_time[MAX_PROCESS];
    int turnaround_time[MAX_PROCESS];
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        completion_time[i] = 0;
    }

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int highest_priority_index = -1;
        int highest_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0 && priority[i] < highest_priority) {
                highest_priority = priority[i];
                highest_priority_index = i;
            }
        }

        if (highest_priority_index == -1) {
            current_time++;
            continue;
        }

        remaining_time[highest_priority_index]--;

        current_time++;

        if (remaining_time[highest_priority_index] == 0) {
            completion_time[highest_priority_index] = current_time;
            turnaround_time[highest_priority_index] = completion_time[highest_priority_index] - arrival_time[highest_priority_index];
            waiting_time[highest_priority_index] = turnaround_time[highest_priority_index] - burst_time[highest_priority_index];
            total_waiting_time += waiting_time[highest_priority_index];
            total_turnaround_time += turnaround_time[highest_priority_index];
            completed_processes++;
        }
    }

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\t\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t\t%d\t\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], priority[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

void roundRobinScheduling(int arrival_time[], int burst_time[], int n) {
    int remaining_time[MAX_PROCESS];
    int completion_time[MAX_PROCESS];
    int waiting_time[MAX_PROCESS];
    int turnaround_time[MAX_PROCESS];
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        completion_time[i] = 0;
    }

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= TIME_QUANTUM) {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    completion_time[i] = current_time;
                    completed_processes++;
                    turnaround_time[i] = completion_time[i] - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                } else {
                    current_time += TIME_QUANTUM;
                    remaining_time[i] -= TIME_QUANTUM;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\t\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int choice;
    char continue_choice = 'y';

    while (continue_choice == 'y' || continue_choice == 'Y') {
        printf("Choose the scheduling algorithm:\n");
        printf("1. Non-preemptive Priority Scheduling\n");
        printf("2. Preemptive Priority Scheduling\n");
        printf("3. Round Robin Scheduling\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int n;
                printf("Enter the number of processes: ");
                scanf("%d", &n);

                int arrival_time[MAX_PROCESS], burst_time[MAX_PROCESS], priority[MAX_PROCESS];

                for (int i = 0; i < n; i++) {
                    printf("\nEnter details for Process %d:\n", i + 1);
                    printf("Arrival Time: ");
                    scanf("%d", &arrival_time[i]);
                    printf("Burst Time: ");
                    scanf("%d", &burst_time[i]);
                    printf("Priority: ");
                    scanf("%d", &priority[i]);
                }

                nonPreemptivePriorityScheduling(arrival_time, burst_time, priority, n);
                break;
            }
            case 2: {
                int n;
                printf("Enter the number of processes: ");
                scanf("%d", &n);

                int arrival_time[MAX_PROCESS], burst_time[MAX_PROCESS], priority[MAX_PROCESS];

                for (int i = 0; i < n; i++) {
                    printf("\nEnter details for Process %d:\n", i + 1);
                    printf("Arrival Time: ");
                    scanf("%d", &arrival_time[i]);
                    printf("Burst Time: ");
                    scanf("%d", &burst_time[i]);
                    printf("Priority: ");
                    scanf("%d", &priority[i]);
                }

                preemptivePriorityScheduling(arrival_time, burst_time, priority, n);
                break;
            }
            case 3: {
                int n;
                printf("Enter the number of processes: ");
                scanf("%d", &n);

                int arrival_time[MAX_PROCESS], burst_time[MAX_PROCESS];

                for (int i = 0; i < n; i++) {
                    printf("\nEnter details for Process %d:\n", i + 1);
                    printf("Arrival Time: ");
                    scanf("%d", &arrival_time[i]);
                    printf("Burst Time: ");
                    scanf("%d", &burst_time[i]);
                }

                roundRobinScheduling(arrival_time, burst_time, n);
                break;
            }
            default:
                printf("Invalid choice.\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continue_choice);
    }

    return 0;
}

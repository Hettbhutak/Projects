 #include <iostream>
#include <vector>
#include <random>

// Process structure representing a process in the system
struct Process {
    std::string name;
    int priority;
    int tickets; 
};

// LotteryScheduler class to manage the lottery process scheduling
class LotteryScheduler {
private:
    std::vector<Process> processes; 
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dis{0, 99}; 
public:
    void addProcess(const std::string& name, int priority, int tickets) {
        processes.push_back({name, priority, tickets});
    }

    // Run the lottery scheduling algorithm
    void runLottery() {
        if (processes.empty()) {
            std::cout << "No processes in the scheduler.\n";
            return;
        }

        int totalTickets = 0;
        for (const auto& process : processes) {
            totalTickets += process.tickets;
        }

        if (totalTickets == 0) {
            std::cout << "No tickets assigned to processes.\n";
            return;
        }

        int winningTicket = dis(gen);

        for (const auto& process : processes) {
            if (winningTicket < process.tickets) {
                std::cout << "Winner: " << process.name << " (Priority: " << process.priority << ")\n";
                break;
            }
            winningTicket -= process.tickets;
        }
    }
};

int main() {
    // Create an instance of LotteryScheduler
    LotteryScheduler scheduler;

    printf("process A || 3 || 30\n");
     printf("process B || 2 || 20\n");
      printf("process C || 1 || 10\n");
    scheduler.addProcess("Process A", 3, 30); // Priority: 3, Tickets: 30
    scheduler.addProcess("Process B", 2, 20); // Priority: 2, Tickets: 20
    scheduler.addProcess("Process C", 1, 10); // Priority: 1, Tickets: 10

    // Run the lottery scheduling algorithm
    scheduler.runLottery();

    return 0;
}

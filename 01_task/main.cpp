#include <iostream>
#include <ctime>
#include <string>
#include <vector>

struct Task {
    std::string task_name;
    std::time_t time_start;
    std::time_t time_end;
};

int main() {
    std::cout << "Implementation of a time tracking program\n";

    std::vector<Task> completed_tasks;
    Task current_task;

    while (true) {
        std::cout << "Enter the command:\n";
        std::cout << "\t->begin - begins tracking a new task.\n"
                     "\t->end - ends tracking of the current task.\n"
                     "\t->status - displays information about all completed tasks\n"
                     "\t->exit - exits the program.\n";
        std::string command;
        std::cin >> command;

        if (command == "begin") {
            std::cout << "Enter the task name:";
            if (!current_task.task_name.empty()) {
                current_task.time_end = std::time(nullptr);
                completed_tasks.push_back(current_task);
                current_task = {};
            }
            std::cin.ignore();
            std::string input_task;
            std::getline(std::cin, input_task);
            current_task.task_name = input_task;
            current_task.time_start = std::time(nullptr);
        } else if (command == "end") {
            if (current_task.task_name.empty()) {
                continue;
            }
            current_task.time_end = std::time(nullptr);
            completed_tasks.push_back(current_task);
            current_task = {};
        } else if (command == "status") {
            std::cout << "Completed tasks:\n";
            if (completed_tasks.empty()) {
                std::cout << "There are no completed tasks.\n";
            } else {
                for (Task task : completed_tasks) {
                    double seconds = std::difftime(task.time_end, task.time_start);
                    int hours = static_cast<int>(seconds) / 3600;
                    int minutes = (static_cast<int>(seconds) % 3600) / 60;
                    std::cout << task.task_name << ": " << hours << " hours, " << minutes << " minutes\n";
                }
            }
            if (!current_task.task_name.empty()) {
                std::cout << "Currently running task: " << current_task.task_name << std::endl;
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid input.\n";
        }
    }

}

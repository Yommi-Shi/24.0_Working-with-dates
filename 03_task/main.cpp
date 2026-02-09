#include <iostream>
#include <ctime>
#include <iomanip>

int main() {
    std::cout << "Implementing a Timer Program\n";

    int minutes = 0, seconds = 0;
    std::cout << "Enter time in mm:ss format:";

    std::tm time_input = {};

    std::cin >> std::get_time(&time_input, "%M:%S");

    minutes = time_input.tm_min;
    seconds = time_input.tm_sec;
    int total_seconds = minutes * 60 + seconds;

    std::time_t start_time = std::time(nullptr);

    while (true) {
        std::time_t now = std::time(nullptr);
        double elapsed = std::difftime(now, start_time);
        int remaining = total_seconds - static_cast<int>(elapsed);
        if (remaining < 0) {
            remaining = 0;
        }
        int rem_minutes = remaining / 60;
        int rem_seconds = remaining % 60;
        std::cout << rem_minutes << ":" << rem_seconds << std::endl;

        if (remaining == 0) {
            break;
        }
        _sleep(1000);
    }
    std::cout << "\nDING! DING! DING!\n";

}

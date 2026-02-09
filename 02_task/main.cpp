#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

struct Friend_Bday {
    std::string name;
    int year, month, day;
};

void get_current_date(int &year, int &month, int &day) {
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
}

int compare_birthdays(int month1, int day1, int month2, int day2) {
    if (month1 < month2) return -1;
    if (month1 > month2) return 1;
    if (day1 < day2) return -1;
    if (day1 > day2) return 1;
    return 0;
}

int main() {
    std::cout << "Implementation of a birthday reminder program\n\n";
    std::cout << "Enter your friends' names and dates of birth.To complete, enter 'end' as the name.\n";

    std::vector<Friend_Bday> friend_bdays;
    std::string name;
    int cur_y, cur_m, cur_d;

    get_current_date(cur_y, cur_m, cur_d);

    while (true) {
        std::cout << "Friend's name:";

        std::getline(std::cin, name);
        if (name == "end") {
            break;
        }

        std::cout << "Date of birth (year/month/day):";
        std::string date;
        std::cin >> date;
        std::cin.ignore();

        int year, month, day;
        char sep;
        std::stringstream ss(date);
        ss >> year >> sep >> month >> sep >> day;

        if (compare_birthdays(month, day, cur_m, cur_d) < 0) {
            continue;
        }
        friend_bdays.push_back({name, year, month, day});
    }

    if (friend_bdays.empty()) {
        std::cout << "There are no upcoming birthdays this year.\n";
        return 0;
    }

    bool found_today = false;
    for (Friend_Bday f : friend_bdays) {
        if (f.month == cur_m && f.day == cur_d) {
            std::cout << "Today is the birthday of: " << f.name << " (" << f.month << "/" << f.day << ")" << std::endl;
            found_today = true;
        }
    }
    if (found_today) {
        return 0;
    }

    Friend_Bday closest = friend_bdays[0];
    bool first = true;
    for (Friend_Bday f :friend_bdays) {
        if (f.month == cur_m && f.day == cur_d) continue;
        if (first || compare_birthdays(f.month, f.day, closest.month, closest.day) < 0) {
            closest = f;
            first = false;
        }
    }

    if (!first) {
        std::cout << "Next birthday: " << closest.name << " - " << closest.month << "/" << closest.day << std::endl;
    }
}

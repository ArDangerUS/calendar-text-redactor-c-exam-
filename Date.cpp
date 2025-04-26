#include "Date.h"
#include <sstream>
#include <iomanip>

Date::Date(int d, int m, int y) : day(1), month(1), year(y) {
    if (!setYear(y) || !setMonth(m) || !setDay(d)) {
        day = 1;
        month = 1;
        year = 2023;
    }
}

bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::getDaysInMonth(int m, int y) const {
    switch (m) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(y) ? 29 : 28;
    default:
        return 0;
    }
}

bool Date::isValidDate(int d, int m, int y) const {
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > getDaysInMonth(m, y)) return false;
    return true;
}

bool Date::setDay(int d) {
    if (isValidDate(d, month, year)) {
        day = d;
        return true;
    }
    return false;
}

bool Date::setMonth(int m) {
    if (m >= 1 && m <= 12) {
        month = m;
        if (day > getDaysInMonth(month, year)) {
            day = getDaysInMonth(month, year);
        }
        return true;
    }
    return false;
}

bool Date::setYear(int y) {
    year = y;
    if (month == 2 && day > getDaysInMonth(month, year)) {
        day = getDaysInMonth(month, year);
    }
    return true;
}

std::string Date::getDayOfWeek() const {
    int m = month;
    int y = year;

    if (m < 3) {
        m += 12;
        y -= 1;
    }

    int h = (day + (13 * (m + 1)) / 5 + y + y / 4 - y / 100 + y / 400) % 7;

    switch (h) {
    case 0: return "Saturday";
    case 1: return "Sunday";
    case 2: return "Monday";
    case 3: return "Tuesday";
    case 4: return "Wednesday";
    case 5: return "Thursday";
    case 6: return "Friday";
    default: return "Unknown";
    }
}

Date& Date::operator++() {
    *this += 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    ++(*this);
    return temp;
}

Date& Date::operator--() {
    *this -= 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp = *this;
    --(*this);
    return temp;
}

Date Date::operator+(int days) const {
    Date result = *this;
    result += days;
    return result;
}

Date Date::operator-(int days) const {
    Date result = *this;
    result -= days;
    return result;
}

int Date::operator-(const Date& other) const {
    auto dateToInt = [](const Date& d) {
        int m = d.month;
        int y = d.year;

        if (m <= 2) {
            m += 12;
            y -= 1;
        }

        int days = d.day;
        days += (153 * m - 457) / 5; 
        days += 365 * y + y / 4 - y / 100 + y / 400; 

        return days;
        };

    return dateToInt(*this) - dateToInt(other);
}

Date& Date::operator+=(int days) {
    if (days < 0) {
        return *this -= -days;
    }

    day += days;

    while (day > getDaysInMonth(month, year)) {
        day -= getDaysInMonth(month, year);
        month++;

        if (month > 12) {
            month = 1;
            year++;
        }
    }

    return *this;
}

Date& Date::operator-=(int days) {
    if (days < 0) {
        return *this += -days;
    }

    while (days >= day) {
        days -= day;
        month--;

        if (month < 1) {
            month = 12;
            year--;
        }

        day = getDaysInMonth(month, year);
    }

    day -= days;
    return *this;
}

bool Date::operator==(const Date& other) const {
    return (day == other.day && month == other.month && year == other.year);
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator<=(const Date& other) const {
    return (*this < other) || (*this == other);
}

bool Date::operator>(const Date& other) const {
    return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "."
        << std::setfill('0') << std::setw(2) << month << "."
        << year;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.toString();
    return os;
}
#include "Time.h"
#include <sstream>
#include <iomanip>

Time::Time(int h, int m, int s) : hour(0), minute(0), second(0) {
    if (!setHour(h) || !setMinute(m) || !setSecond(s)) {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

bool Time::isValidTime(int h, int m, int s) const {
    return (h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >= 0 && s < 60);
}

bool Time::setHour(int h) {
    if (h >= 0 && h < 24) {
        hour = h;
        return true;
    }
    return false;
}

bool Time::setMinute(int m) {
    if (m >= 0 && m < 60) {
        minute = m;
        return true;
    }
    return false;
}

bool Time::setSecond(int s) {
    if (s >= 0 && s < 60) {
        second = s;
        return true;
    }
    return false;
}

int Time::toSeconds() const {
    return hour * 3600 + minute * 60 + second;
}

Time& Time::operator++() {
    *this += 1;
    return *this;
}

Time Time::operator++(int) {
    Time temp = *this;
    ++(*this);
    return temp;
}

Time& Time::operator--() {
    *this -= 1;
    return *this;
}

Time Time::operator--(int) {
    Time temp = *this;
    --(*this);
    return temp;
}

Time Time::operator+(int seconds) const {
    Time result = *this;
    result += seconds;
    return result;
}

Time Time::operator-(int seconds) const {
    Time result = *this;
    result -= seconds;
    return result;
}

int Time::operator-(const Time& other) const {
    return toSeconds() - other.toSeconds();
}

Time& Time::operator+=(int seconds) {
    if (seconds < 0) {
        return *this -= -seconds;
    }

    int totalSeconds = toSeconds() + seconds;

    totalSeconds %= 86400; // 24*60*60

    hour = totalSeconds / 3600;
    totalSeconds %= 3600;
    minute = totalSeconds / 60;
    second = totalSeconds % 60;

    return *this;
}

Time& Time::operator-=(int seconds) {
    if (seconds < 0) {
        return *this += -seconds;
    }

    int totalSeconds = toSeconds() - seconds;

    while (totalSeconds < 0) {
        totalSeconds += 86400; 
    }

    hour = totalSeconds / 3600;
    totalSeconds %= 3600;
    minute = totalSeconds / 60;
    second = totalSeconds % 60;

    return *this;
}

bool Time::operator==(const Time& other) const {
    return (hour == other.hour && minute == other.minute && second == other.second);
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<(const Time& other) const {
    return toSeconds() < other.toSeconds();
}

bool Time::operator<=(const Time& other) const {
    return toSeconds() <= other.toSeconds();
}

bool Time::operator>(const Time& other) const {
    return toSeconds() > other.toSeconds();
}

bool Time::operator>=(const Time& other) const {
    return toSeconds() >= other.toSeconds();
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setfill('0') << std::setw(2) << minute << ":"
        << std::setfill('0') << std::setw(2) << second;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << time.toString();
    return os;
}
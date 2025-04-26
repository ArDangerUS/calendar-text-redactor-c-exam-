#ifndef TIME_H
#define TIME_H

#include <string>
#include <ostream>

class Time {
private:
    int hour;
    int minute;
    int second;

    bool isValidTime(int h, int m, int s) const;

public:

    Time(int h = 0, int m = 0, int s = 0);

    // Getters
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    // Setters
    bool setHour(int h);
    bool setMinute(int m);
    bool setSecond(int s);

    int toSeconds() const;

    Time& operator++();    
    Time operator++(int); 
    Time& operator--();  
    Time operator--(int);  

  
    Time operator+(int seconds) const;
    Time operator-(int seconds) const;
    int operator-(const Time& other) const;
    Time& operator+=(int seconds);
    Time& operator-=(int seconds);

    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator>=(const Time& other) const;

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif // TIME_H
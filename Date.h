#ifndef DATE_H
#define DATE_H

#include <string>
#include <ostream>

class Date {
private:
    int day;
    int month;
    int year;

    bool isValidDate(int d, int m, int y) const;
    int getDaysInMonth(int m, int y) const;
    bool isLeapYear(int y) const;

public:

    Date(int d = 1, int m = 1, int y = 2023);

    // Getters
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Setters
    bool setDay(int d);
    bool setMonth(int m);
    bool setYear(int y);

    std::string getDayOfWeek() const;

    
    Date& operator++();   
    Date operator++(int);  
    Date& operator--();    
    Date operator--(int);

   
    Date operator+(int days) const;
    Date operator-(int days) const;
    int operator-(const Date& other) const;
    Date& operator+=(int days);
    Date& operator-=(int days);

 
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;

    
    std::string toString() const;

   
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif // DATE_H
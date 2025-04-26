#ifndef CALENDAR_H
#define CALENDAR_H

#include "Date.h"
#include "Event.h"
#include <vector>
#include <map>
#include <functional>
#include <memory>

class Calendar {
private:
    std::vector<std::shared_ptr<Event>> events;
    Date currentDate; 

    int getDayOfWeek(int day, int month, int year) const;
    int getDaysInMonth(int month, int year) const;
    bool isLeapYear(int year) const;
    std::string getMonthName(int month) const;

   
    std::vector<std::shared_ptr<Event>> filterEvents(std::function<bool(const Event&)> predicate) const;

public:
   
    Calendar(const Date& date = Date());

    void addEvent(const Event& event);
    void addEvent(std::shared_ptr<Event> event);
    void removeEvent(const Event& event);

    void nextMonth();
    void previousMonth();
    void nextYear();
    void previousYear();

    
    std::string displayMonth() const;
    std::string displayYear() const;

   
    std::vector<std::shared_ptr<Event>> getEventsForDay(const Date& date) const;
    std::vector<std::shared_ptr<Event>> getEventsForMonth(int month, int year) const;
    std::vector<std::shared_ptr<Event>> getEventsInDateRange(const Date& start, const Date& end) const;
    std::vector<std::shared_ptr<Event>> getEventsByType(EventType type) const;
    std::vector<std::shared_ptr<Event>> getEventsByPriority(EventPriority priority) const;

   
    Date getCurrentDate() const { return currentDate; }
    void setCurrentDate(const Date& date) { currentDate = date; }

   
    static Date calculateSemesterEndDate(const Date& startDate, int weeks);
};

#endif // CALENDAR_H
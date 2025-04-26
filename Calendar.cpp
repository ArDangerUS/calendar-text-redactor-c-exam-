#include "Calendar.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

Calendar::Calendar(const Date& date) : currentDate(date) {}

void Calendar::addEvent(const Event& event) {
    events.push_back(std::make_shared<Event>(event));
}

void Calendar::addEvent(std::shared_ptr<Event> event) {
    events.push_back(event);
}

void Calendar::removeEvent(const Event& event) {
    auto it = std::remove_if(events.begin(), events.end(),
        [&event](const std::shared_ptr<Event>& e) {
            return *e == event;
        });

    if (it != events.end()) {
        events.erase(it, events.end());
    }
}

bool Calendar::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Calendar::getDaysInMonth(int month, int year) const {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}

std::string Calendar::getMonthName(int month) const {
    const std::string monthNames[] = { "", "January", "February", "March", "April", "May", "June",
                                      "July", "August", "September", "October", "November", "December" };
    if (month >= 1 && month <= 12) {
        return monthNames[month];
    }
    return "";
}

int Calendar::getDayOfWeek(int day, int month, int year) const {
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    int k = year % 100;
    int j = year / 100;
    int h = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    return (h + 5) % 7 + 1;
}

void Calendar::nextMonth() {
    if (currentDate.getMonth() == 12) {
        currentDate = Date(1, 1, currentDate.getYear() + 1);
    }
    else {
        currentDate = Date(1, currentDate.getMonth() + 1, currentDate.getYear());
    }
}

void Calendar::previousMonth() {
    if (currentDate.getMonth() == 1) {
        currentDate = Date(1, 12, currentDate.getYear() - 1);
    }
    else {
        currentDate = Date(1, currentDate.getMonth() - 1, currentDate.getYear());
    }
}

void Calendar::nextYear() {
    currentDate = Date(currentDate.getDay(), currentDate.getMonth(), currentDate.getYear() + 1);
}

void Calendar::previousYear() {
    currentDate = Date(currentDate.getDay(), currentDate.getMonth(), currentDate.getYear() - 1);
}

std::vector<std::shared_ptr<Event>> Calendar::filterEvents(std::function<bool(const Event&)> predicate) const {
    std::vector<std::shared_ptr<Event>> result;
    for (const auto& event : events) {
        if (predicate(*event)) {
            result.push_back(event);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Event>> Calendar::getEventsForDay(const Date& date) const {
    return filterEvents([&date](const Event& event) {
        return event.getDate() == date;
        });
}

std::vector<std::shared_ptr<Event>> Calendar::getEventsForMonth(int month, int year) const {
    return filterEvents([month, year](const Event& event) {
        return event.getDate().getMonth() == month && event.getDate().getYear() == year;
        });
}

std::vector<std::shared_ptr<Event>> Calendar::getEventsInDateRange(const Date& start, const Date& end) const {
    return filterEvents([&start, &end](const Event& event) {
        return event.getDate() >= start && event.getDate() <= end;
        });
}

std::vector<std::shared_ptr<Event>> Calendar::getEventsByType(EventType type) const {
    return filterEvents([type](const Event& event) {
        return event.getType() == type;
        });
}

std::vector<std::shared_ptr<Event>> Calendar::getEventsByPriority(EventPriority priority) const {
    return filterEvents([priority](const Event& event) {
        return event.getPriority() == priority;
        });
}

std::string Calendar::displayMonth() const {
    std::ostringstream oss;
    int month = currentDate.getMonth();
    int year = currentDate.getYear();

    oss << "\n" << getMonthName(month) << " " << year << "\n";
    oss << "Mo Tu We Th Fr Sa Su\n";

    int firstDay = getDayOfWeek(1, month, year);
    int daysInMonth = getDaysInMonth(month, year);

    for (int i = 1; i < firstDay; ++i) {
        oss << "   ";
    }

    for (int day = 1; day <= daysInMonth; ++day) {
        oss << std::setw(2) << day << " ";

        Date checkDate(day, month, year);
        auto dayEvents = getEventsForDay(checkDate);

        if (checkDate == currentDate) {
            oss << "*";
        }
        else if (!dayEvents.empty()) {
            bool hasHighPriority = false;
            for (const auto& event : dayEvents) {
                if (event->getPriority() == EventPriority::HIGH ||
                    event->getPriority() == EventPriority::URGENT) {
                    hasHighPriority = true;
                    break;
                }
            }

            if (hasHighPriority) {
                oss << "!!";
            }
            else {
                oss << "!";
            }
        }
        else {
            oss << " ";
        }

        if ((firstDay + day - 1) % 7 == 0) {
            oss << "\n";
        }
    }

    oss << "\n";

    auto monthEvents = getEventsForMonth(month, year);
    if (!monthEvents.empty()) {
        oss << "\nEvents this month:\n";
        for (const auto& event : monthEvents) {
            oss << event->getDate() << " - " << event->getTitle();
            if (event->hasTime()) {
                oss << " at " << event->getTime().value();
            }
            oss << " [" << Event::priorityToString(event->getPriority()) << "]\n";
        }
    }

    return oss.str();
}

std::string Calendar::displayYear() const {
    std::ostringstream oss;
    int year = currentDate.getYear();

    oss << "\n" << year << "\n\n";

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            int month = row * 3 + col + 1;
            oss << std::setw(10) << getMonthName(month).substr(0, 3) << "          ";
        }
        oss << "\n";

        for (int col = 0; col < 3; ++col) {
            oss << "Mo Tu We Th Fr Sa Su   ";
        }
        oss << "\n";

        int maxWeeks = 6;

        for (int week = 0; week < maxWeeks; ++week) {
            for (int col = 0; col < 3; ++col) {
                int month = row * 3 + col + 1;
                int firstDay = getDayOfWeek(1, month, year);
                int daysInMonth = getDaysInMonth(month, year);

                for (int weekDay = 1; weekDay <= 7; ++weekDay) {
                    int day = week * 7 + weekDay - firstDay + 1;

                    if (day > 0 && day <= daysInMonth) {
                        Date checkDate(day, month, year);
                        oss << std::setw(2) << day;

                        if (checkDate == currentDate) {
                            oss << "*";
                        }
                        else {
                            auto dayEvents = getEventsForDay(checkDate);
                            if (!dayEvents.empty()) {
                                bool hasHighPriority = false;
                                for (const auto& event : dayEvents) {
                                    if (event->getPriority() == EventPriority::HIGH ||
                                        event->getPriority() == EventPriority::URGENT) {
                                        hasHighPriority = true;
                                        break;
                                    }
                                }

                                if (hasHighPriority) {
                                    oss << "!!";
                                }
                                else {
                                    oss << "!";
                                }
                            }
                            else {
                                oss << " ";
                            }
                        }
                    }
                    else {
                        oss << "   ";
                    }
                }

                oss << "  ";
            }
            oss << "\n";
        }
    }

    return oss.str();
}


Date Calendar::calculateSemesterEndDate(const Date& startDate, int weeks) {
    return startDate + (weeks * 7);
}
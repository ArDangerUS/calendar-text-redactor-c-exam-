#ifndef EVENT_H
#define EVENT_H

#include "Date.h"
#include "Time.h"
#include <string>
#include <optional>

enum class EventType {
    MEETING,
    APPOINTMENT,
    REMINDER,
    DEADLINE,
    CELEBRATION,
    OTHER
};

enum class EventPriority {
    LOW,
    MEDIUM,
    HIGH,
    URGENT
};

class Event {
private:
    Date date;
    std::optional<Time> time; 
    EventType type;
    EventPriority priority;
    std::string title;
    std::string description;

public:

    Event(const Date& d, const std::string& t, EventType et = EventType::OTHER,
        EventPriority p = EventPriority::MEDIUM, const std::string& desc = "");

    Event(const Date& d, const Time& tm, const std::string& t, EventType et = EventType::OTHER,
        EventPriority p = EventPriority::MEDIUM, const std::string& desc = "");

    // Getters
    const Date& getDate() const { return date; }
    const std::optional<Time>& getTime() const { return time; }
    EventType getType() const { return type; }
    EventPriority getPriority() const { return priority; }
    const std::string& getTitle() const { return title; }
    const std::string& getDescription() const { return description; }

    // Setters
    void setDate(const Date& d) { date = d; }
    void setTime(const Time& t) { time = t; }
    void clearTime() { time.reset(); } 
    void setType(EventType t) { type = t; }
    void setPriority(EventPriority p) { priority = p; }
    void setTitle(const std::string& t) { title = t; }
    void setDescription(const std::string& d) { description = d; }

    
    bool hasTime() const { return time.has_value(); }

   
    bool operator==(const Event& other) const;
    bool operator!=(const Event& other) const;
    bool operator<(const Event& other) const;
    bool operator<=(const Event& other) const;
    bool operator>(const Event& other) const;
    bool operator>=(const Event& other) const;


    std::string toString() const;

  
    static std::string typeToString(EventType type);
    static std::string priorityToString(EventPriority priority);

    friend std::ostream& operator<<(std::ostream& os, const Event& event);
};

#endif // EVENT_H
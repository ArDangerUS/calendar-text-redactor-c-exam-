#include "Event.h"
#include <sstream>

Event::Event(const Date& d, const std::string& t, EventType et, EventPriority p, const std::string& desc)
    : date(d), time(std::nullopt), type(et), priority(p), title(t), description(desc) {}

Event::Event(const Date& d, const Time& tm, const std::string& t, EventType et, EventPriority p, const std::string& desc)
    : date(d), time(tm), type(et), priority(p), title(t), description(desc) {}

bool Event::operator==(const Event& other) const {
    if (date != other.date) return false;

    if (time.has_value() && other.time.has_value()) {
        return time.value() == other.time.value();
    }

    return true;
}

bool Event::operator!=(const Event& other) const {
    return !(*this == other);
}

bool Event::operator<(const Event& other) const {
    if (date < other.date) return true;
    if (date > other.date) return false;

  
    if (time.has_value() && other.time.has_value()) {
        return time.value() < other.time.value();
    }

   
    if (time.has_value()) return true;
    return false;
}

bool Event::operator<=(const Event& other) const {
    return (*this < other) || (*this == other);
}

bool Event::operator>(const Event& other) const {
    return !(*this <= other);
}

bool Event::operator>=(const Event& other) const {
    return !(*this < other);
}

std::string Event::typeToString(EventType type) {
    switch (type) {
    case EventType::MEETING: return "Meeting";
    case EventType::APPOINTMENT: return "Appointment";
    case EventType::REMINDER: return "Reminder";
    case EventType::DEADLINE: return "Deadline";
    case EventType::CELEBRATION: return "Celebration";
    case EventType::OTHER: return "Other";
    default: return "Unknown";
    }
}

std::string Event::priorityToString(EventPriority priority) {
    switch (priority) {
    case EventPriority::LOW: return "Low";
    case EventPriority::MEDIUM: return "Medium";
    case EventPriority::HIGH: return "High";
    case EventPriority::URGENT: return "Urgent";
    default: return "Unknown";
    }
}

std::string Event::toString() const {
    std::ostringstream oss;
    oss << "[" << priorityToString(priority) << "] " << title << " (" << typeToString(type) << ")\n";
    oss << "Date: " << date;

    if (time.has_value()) {
        oss << ", Time: " << time.value();
    }

    if (!description.empty()) {
        oss << "\nDescription: " << description;
    }

    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << event.toString();
    return os;
}
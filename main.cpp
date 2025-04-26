#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "Date.h"
#include "Time.h"
#include "Event.h"
#include "Calendar.h"
#include "screen.h"
#include "dictionary.h"
#include "deque.h"


void testDateAndTime() {
    std::cout << "===== Testing Date and Time Classes =====\n\n";


    Date today(25, 4, 2025);
    std::cout << "Today's date: " << today << std::endl;
    std::cout << "Day of week: " << today.getDayOfWeek() << std::endl;

    Date tomorrow = today + 1;
    std::cout << "Tomorrow: " << tomorrow << std::endl;

    Date nextWeek = today + 7;
    std::cout << "Next week: " << nextWeek << std::endl;

    int daysBetween = nextWeek - today;
    std::cout << "Days between: " << daysBetween << std::endl;

   
    std::cout << "Is today < tomorrow? " << (today < tomorrow ? "Yes" : "No") << std::endl;
    std::cout << "Is today == today? " << (today == today ? "Yes" : "No") << std::endl;

    
    Time now(14, 30, 0);
    std::cout << "\nCurrent time: " << now << std::endl;

    Time later = now + 3600; 
    std::cout << "An hour later: " << later << std::endl;

    int secondsBetween = later - now;
    std::cout << "Seconds between: " << secondsBetween << std::endl;

  
    std::cout << "Is now < later? " << (now < later ? "Yes" : "No") << std::endl;
    std::cout << "Is now == now? " << (now == now ? "Yes" : "No") << std::endl;

    std::cout << "\n";
}


void testEvent() {
    std::cout << "===== Testing Event Class =====\n\n";


    Date meetingDate(26, 4, 2025);
    Time meetingTime(10, 0, 0);

    Event meetingWithTime(meetingDate, meetingTime, "Team Meeting",
        EventType::MEETING, EventPriority::HIGH,
        "Discuss project progress");

    Event birthdayWithoutTime(Date(15, 5, 2025), "Birthday Party",
        EventType::CELEBRATION, EventPriority::MEDIUM,
        "Celebrate John's birthday");


    std::cout << "Event with time:\n" << meetingWithTime << "\n\n";
    std::cout << "Event without time:\n" << birthdayWithoutTime << "\n\n";


    std::cout << "Is meeting before birthday? "
        << (meetingWithTime < birthdayWithoutTime ? "Yes" : "No") << "\n\n";

    std::cout << "Modifying meeting event...\n";
    meetingWithTime.setTitle("Urgent Team Meeting");
    meetingWithTime.setPriority(EventPriority::URGENT);
    std::cout << "Modified event:\n" << meetingWithTime << "\n\n";
}


void testCalendar() {
    std::cout << "===== Testing Calendar Class =====\n\n";

   
    Calendar calendar(Date(25, 4, 2025));


    Event meeting(Date(27, 4, 2025), Time(10, 0, 0), "Team Meeting",
        EventType::MEETING, EventPriority::HIGH);

    Event deadline(Date(30, 4, 2025), Time(23, 59, 59), "Project Deadline",
        EventType::DEADLINE, EventPriority::URGENT);

    Event birthday(Date(15, 5, 2025), "Birthday",
        EventType::CELEBRATION, EventPriority::MEDIUM);

    calendar.addEvent(meeting);
    calendar.addEvent(deadline);
    calendar.addEvent(birthday);

  
    std::cout << "Current Month Calendar:\n" << calendar.displayMonth() << std::endl;

 
    std::cout << "Navigating to next month...\n";
    calendar.nextMonth();
    std::cout << calendar.displayMonth() << std::endl;

    calendar.previousMonth();
    std::cout << "Full Year Calendar:\n" << calendar.displayYear() << std::endl;

    std::cout << "High priority events:\n";
    auto highPriorityEvents = calendar.getEventsByPriority(EventPriority::HIGH);
    for (const auto& event : highPriorityEvents) {
        std::cout << "- " << event->getTitle() << " on " << event->getDate() << std::endl;
    }

    std::cout << "\nDeadline events:\n";
    auto deadlineEvents = calendar.getEventsByType(EventType::DEADLINE);
    for (const auto& event : deadlineEvents) {
        std::cout << "- " << event->getTitle() << " on " << event->getDate() << std::endl;
    }

    std::cout << std::endl;
}


void calculateSemesterEnd() {
    std::cout << "===== Task 4: Calculate Semester End Date =====\n\n";

    Date semesterStart(1, 9, 2025);
    std::cout << "Semester start date: " << semesterStart << std::endl;

    int semesterWeeks = 15;
    std::cout << "Semester length: " << semesterWeeks << " weeks" << std::endl;

  
    Date semesterEnd = Calendar::calculateSemesterEndDate(semesterStart, semesterWeeks);
    std::cout << "Semester end date: " << semesterEnd << std::endl;
    std::cout << "Day of week: " << semesterEnd.getDayOfWeek() << std::endl;

    std::cout << std::endl;
}


void checkBirthdays() {
    std::cout << "===== Task 5: Birthday Days of Week =====\n\n";


    Date myBirthday(17, 2, 2006);
    std::cout << "My birthday (" << myBirthday << "): "
        << myBirthday.getDayOfWeek() << std::endl;

   
    struct FamousPerson {
        std::string name;
        Date birthday;
    };

    FamousPerson famousPeople[] = {
        {"Albert Einstein", Date(14, 3, 1879)},
        {"Marie Curie", Date(7, 11, 1867)},
        {"Leonardo da Vinci", Date(15, 4, 1452)},
        {"Ada Lovelace", Date(10, 12, 1815)},
        {"Alan Turing", Date(23, 6, 1912)}
    };

    for (const auto& person : famousPeople) {
        std::cout << person.name << "'s birthday (" << person.birthday << "): "
            << person.birthday.getDayOfWeek() << std::endl;
    }

    std::cout << std::endl;
}

void evalScreenFunctionality() {
    std::cout << "\n*************** SECTION 6-7: Screen Implementation ***************\n" << std::endl;

    try {
        Screen screen("lorem.txt");
        screen.display();

        std::cout << ">> Moving forward one page" << std::endl;
        screen.scrollForward();
        screen.display();

        std::cout << ">> Moving back one page" << std::endl;
        screen.scrollBackward();
        screen.display();

        std::cout << ">> Editing current paragraph" << std::endl;
        screen.modifyLine("This paragraph has been updated with new content.");
        screen.display();

        std::cout << ">> Adding new paragraph" << std::endl;
        screen.insertLine("Here's a fresh paragraph with additional information.");
        screen.display();

        std::cout << ">> Removing current paragraph" << std::endl;
        screen.deleteLine();
        screen.display();

        Screen screenCopy(screen);
        std::cout << ">> Copy constructor test:" << std::endl;
        screenCopy.display();

        Screen screenMove(std::move(screenCopy));
        std::cout << ">> Move constructor test:" << std::endl;
        screenMove.display();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

void evalDictionaryFunctionality() {
    std::cout << "\n*************** SECTION 8: Dictionary Implementation ***************\n" << std::endl;

    try {
        Dictionary dict("lorem.txt");

        std::cout << "Dictionary without frequencies:" << std::endl;
        dict.display(false);

        std::cout << "Dictionary with frequencies:" << std::endl;
        dict.display(true);

        dict.setWordStatus("lorem", WordStatus::New);
        dict.setWordStatus("ipsum", WordStatus::Learning);
        dict.setWordStatus("dolor", WordStatus::Learned);
        dict.setWordStatus("sit", WordStatus::Ignored);

        std::cout << "Dictionary after word status updates:" << std::endl;
        dict.display(false);

        Dictionary dict2("lorem_2.txt");
        dict2.setWordStatus("lorem", WordStatus::Learned);
        dict2.setWordStatus("amet", WordStatus::New);
        dict2.setWordStatus("consectetur", WordStatus::Learning);

        std::cout << "Second test dictionary:" << std::endl;
        dict2.display(false);

        Dictionary unionDict = dict + dict2;
        std::cout << "Combined dictionaries (union):" << std::endl;
        unionDict.display(false);

        Dictionary intersectionDict = dict.intersection(dict2);
        std::cout << "Common words (intersection):" << std::endl;
        intersectionDict.display(false);

        std::vector<std::string> learningWords = unionDict.getWordsByStatus(WordStatus::Learning);
        std::cout << "Words currently being learned:" << std::endl;
        for (const auto& word : learningWords) {
            std::cout << " * " << word << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}

void evalDequeNVI() {
    std::cout << "\n*************** SECTION 9: Deque with NVI Pattern ***************\n" << std::endl;

    ArrayDeque<int> arrayDeque;
    std::cout << "======= Testing ArrayDeque Implementation =======" << std::endl;

    std::cout << "Adding elements to deque" << std::endl;
    arrayDeque.pushBack(10);
    arrayDeque.pushBack(20);
    arrayDeque.pushBack(30);
    arrayDeque.pushFront(0);
    arrayDeque.pushFront(-10);

    std::cout << "Current size: " << arrayDeque.size() << std::endl;
    std::cout << "First element: " << arrayDeque.front() << std::endl;
    std::cout << "Last element: " << arrayDeque.back() << std::endl;

    std::cout << "Removing from front: " << arrayDeque.popFront() << std::endl;
    std::cout << "Removing from back: " << arrayDeque.popBack() << std::endl;
    std::cout << "Size after removals: " << arrayDeque.size() << std::endl;

    ListDeque<int> listDeque;
    std::cout << "\n======= Testing ListDeque Implementation =======" << std::endl;

    std::cout << "Adding elements to deque" << std::endl;
    listDeque.pushBack(100);
    listDeque.pushBack(200);
    listDeque.pushBack(300);
    listDeque.pushFront(0);
    listDeque.pushFront(-100);

    std::cout << "Current size: " << listDeque.size() << std::endl;
    std::cout << "First element: " << listDeque.front() << std::endl;
    std::cout << "Last element: " << listDeque.back() << std::endl;

    std::cout << "Removing from front: " << listDeque.popFront() << std::endl;
    std::cout << "Removing from back: " << listDeque.popBack() << std::endl;
    std::cout << "Size after removals: " << listDeque.size() << std::endl;
}

void evalDequeComposition() {
    std::cout << "\n*************** SECTION 10: Deque with Composition ***************\n" << std::endl;

    ArrayDequeComposition<int> arrayDeque;
    std::cout << "======= Testing ArrayDequeComposition =======" << std::endl;

    std::cout << "Adding elements to deque" << std::endl;
    arrayDeque.pushBack(15);
    arrayDeque.pushBack(25);
    arrayDeque.pushBack(35);
    arrayDeque.pushFront(5);
    arrayDeque.pushFront(-5);

    std::cout << "Current size: " << arrayDeque.size() << std::endl;
    std::cout << "First element: " << arrayDeque.front() << std::endl;
    std::cout << "Last element: " << arrayDeque.back() << std::endl;

    std::cout << "Removing from front: " << arrayDeque.popFront() << std::endl;
    std::cout << "Removing from back: " << arrayDeque.popBack() << std::endl;
    std::cout << "Size after removals: " << arrayDeque.size() << std::endl;

    ListDequeComposition<int> listDeque;
    std::cout << "\n======= Testing ListDequeComposition =======" << std::endl;

    std::cout << "Adding elements to deque" << std::endl;
    listDeque.pushBack(150);
    listDeque.pushBack(250);
    listDeque.pushBack(350);
    listDeque.pushFront(50);
    listDeque.pushFront(-50);

    std::cout << "Current size: " << listDeque.size() << std::endl;
    std::cout << "First element: " << listDeque.front() << std::endl;
    std::cout << "Last element: " << listDeque.back() << std::endl;

    std::cout << "Removing from front: " << listDeque.popFront() << std::endl;
    std::cout << "Removing from back: " << listDeque.popBack() << std::endl;
    std::cout << "Size after removals: " << listDeque.size() << std::endl;

    std::cout << "\n*************** Design Pattern Analysis ***************" << std::endl;
    std::cout << "Composition offers several advantages over inheritance in this context:" << std::endl;
    std::cout << "1. It better represents the 'has-a' relationship between Deque and its implementation" << std::endl;
    std::cout << "2. It avoids potential issues with the inheritance hierarchy" << std::endl;
    std::cout << "3. It provides stronger encapsulation of implementation details" << std::endl;
    std::cout << "4. It allows for easier runtime switching of implementation strategies" << std::endl;
}

int main() {
    testCalendar();
    testDateAndTime();
    testEvent();
    calculateSemesterEnd();
    checkBirthdays();
    evalScreenFunctionality();
    evalDictionaryFunctionality();
    evalDequeNVI();
    evalDequeComposition();

    return 0;
}
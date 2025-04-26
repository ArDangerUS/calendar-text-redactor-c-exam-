Overview
This project implements various classes and functionalities related to date and time management, event scheduling, calendar operations, text display, dictionary building, and deque operations. The project is divided into several tasks, each focusing on a specific aspect of the overall functionality.

Tasks
1. Date and Time Classes
Implemented classes Date and Time with support for:

Validation
Getters and setters
Determining the day of the week
Increment and decrement operations
Arithmetic operations (+, -, +=, -=)
Comparison operators
Output utilities
Ensured constructors and state invariance.

2. Event Class
Created the Event class containing:

Date
Time
Type
Priority
Title
Description
Supported events with and without time, provided access to fields, formatted output, and comparison by date and time.

3. Calendar Class
Implemented the Calendar class with capabilities to:

Display a specific month or year
Navigate between months
Highlight current and important dates
Integrate with Event class
Filter events by type, priority, month, or specific period
4. Semester End Date Calculation
Calculated the end date of a semester given its duration in weeks and the start date.

5. Day of the Week Calculation
Using the calendar, determined the day of the week for:

Your birthday
Birthdays of notable figures in science and culture (of your choice)
6. Screen Class
Defined the Screen class to display a fragment of text starting from a specific position. Implemented scrolling forward and backward. Text for display, consisting of n paragraphs with m sentences each, can be created using the =lorem(n,m) command in Microsoft Word and saved to a text file. Used std::ifstream for reading text from the file.

7. Screen Copying and Moving
Ensured copying and moving of screens. Implemented text editing within the screen.

8. Dictionary Class
Developed the Dictionary class to build a dictionary from text:

Sorted words lexicographically or by frequency
Tracked foreign words with specified statuses (e.g., new, learning, learned, ignored)
Implemented operations for dictionary addition, union, intersection, and output utilities
9. Deque Interface Inheritance
Built interface inheritance for bidirectional queues Deque<T> (with T as any type) using array-based and list-based queues. Applied Non-Virtual Interface (NVI) pattern.

10. Deque Implementation Inheritance
Constructed implementation inheritance for bidirectional queues Deque<T, Implementation> using array-based ArrayDeque<T> and list-based ListDeque<T>. Compared the use of private inheritance and composition (aggregation).

Usage
To use the classes and functionalities provided in this project, follow the instructions below:

Clone the repository:


Navigate to the project directory:


Build the project using your preferred build system (e.g., make, cmake).

Run the executable to test the functionalities.

Contributing
Contributions are welcome! Please fork the repository and submit pull requests for any improvements or bug fixes.

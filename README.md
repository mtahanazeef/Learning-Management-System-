# Learning-Management-System-
This project is a console-based Learning Management System built using object-oriented programming principles. The goal is simple: simulate the core functions of a basic LMS while enforcing role separation, file-based storage, and structured navigation. The code isn’t just a collection of menus. It uses inheritance, polymorphism, encapsulation, and composition to organize responsibilities in a way that scales better than a procedural design.

The system starts by showing developer information, collecting the user’s campus name, and validating it. After that, the main menu lets the user log in as an Admin, Teacher, or Student. Each role inherits from a common User base class but implements its own authentication and menu functions. This keeps the logic isolated and avoids bloated conditional code.

The Admin module is responsible for adding and viewing student records. Records are stored in a plain text file, and the admin can append new entries or load and display all existing ones. The implementation is simple, but it demonstrates basic file handling and persistent storage without a database.

The Teacher module lets instructors upload lecture notes and manage assignments. Lecture uploads write directly to a file, and assignment management reuses shared features. This keeps the system consistent and avoids duplicate logic. The teacher login requires a fixed username and ID, acting as a basic security placeholder.

The Student module is the most feature-heavy. Students log in using a username and a roll number that must exist in the stored records. After authentication, students can access their timetable, view attendance, calculate GPA, read lecture notes, and handle assignments. The lecture notes and assignments load content from external files, giving the system a realistic feel despite its simplicity. The GPA calculator is straightforward: it collects grades, computes an average, and prints the result.

The project also includes a Developer class, which acts as a small branding feature, and a University class that performs an initial campus validation. While these aren’t essential to the system’s core functionality, they help demonstrate additional use of classes and structured initialization.

Utility functions handle common tasks like clearing the screen, delays, uppercase conversion, and basic loading animations. They keep repetitive code out of the main logic. The system uses unique_ptr for memory safety and tries to avoid raw pointers where possible.

Overall, the project demonstrates a practical application of OOP to build a multi-user LMS with menus, file handling, inheritance, and modular class design. It’s not enterprise-level software, but it’s a solid intermediate-level project that shows you understand how to structure an application beyond one big main function.

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <exception>
#include <iomanip>
#include <algorithm>

using namespace std;

// ==================== CONSTANTS AND CONFIGURATION ====================
namespace Config {
    const string ADMIN_USERNAME = "RIAZ";
    const int ADMIN_ID = 100;
    const string STUDENT_USERNAME = "Student";
    const string INVALID_CAMPUS = "Dehli";
    const string STUDENT_RECORD_FILE = "StudentRecord.txt";
    const string COURSE_FILE_OOP = "OOP.txt";
    const string COURSE_FILE_CS = "CS.txt";
    const string COURSE_FILE_OOP_LAB = "OOP-LAB.txt";
}

// ==================== UTILITY FUNCTIONS ====================
namespace Utility {
    void clearScreen() {
        system("cls");
    }
    
    void sleep(int milliseconds) {
        Sleep(milliseconds);
    }
    
    void showLoading(const string& message = "Loading") {
        cout << "\n\t" << message;
        for(int i = 0; i < 5; i++) {
            cout << ".";
            sleep(300);
        }
        cout << endl;
    }
    
    void pressAnyKeyToContinue() {
        cout << "\n\nPress any key to continue...";
        _getch();
    }
    
    string toUpper(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
}

// ==================== BASE CLASSES ====================
class Developer {
public:
    virtual void display() = 0;
    virtual ~Developer() = default;
};

class User {
protected:
    string name;
    string id;
    int semester;
    
public:
    User(const string& name = "", const string& id = "", int sem = 0) 
        : name(name), id(id), semester(sem) {}
    
    virtual ~User() = default;
    virtual void menu() = 0;
    
    // Getters
    string getName() const { return name; }
    string getId() const { return id; }
    int getSemester() const { return semester; }
};

// ==================== DEVELOPER INFORMATION ====================
class SubDeveloper : public Developer {
public:
    void display() override {
        cout << "\x1b[91m";
        cout << "\n\t\t\t\t\t\x1b[1m\x1b[3mWelcome to our Learning Management System\n\n\n";
        cout << "\n\n\t\t\t\t\t MADE BY :" << endl;
        cout << "\t\t\t\t\t---------------------------------------" << endl;
        cout << "\t\t\t\t\t\tMUHAMMAD TAHA NAZEEF (024) " << endl;
        cout << "\t\t\t\t\t\tATTA MUSTAFA         (008) " << endl;
        cout << "\t\t\t\t\t---------------------------------------" << endl;
        cout << "\n\n\n\n\n\tLoading\x1b[5m.....\x1b[25m\n";
        cout << "\x1b[0m";
    }
};

// ==================== UNIVERSITY CLASS ====================
class University {
private:
    string campus;
    
public:
    University() {
        displayHeader();
        getCampusInput();
        Utility::clearScreen();
    }
    
private:
    void displayHeader() {
        cout << "\x1b[33m";
        cout << "\n\n\t\t\t\t  **********************" << endl;
        cout << "\t\t\t\t  *    University      *" << endl;
        cout << "\t\t\t\t  **********************" << endl;
        cout << "\x1b[37m";
    }
    
    void getCampusInput() {
        try {
            cout << "\n\tEnter your campus : ";
            cin >> campus;
            if (Utility::toUpper(campus) == Utility::toUpper(Config::INVALID_CAMPUS)) {
                throw invalid_argument("\tInvalid Campus!!!\n");
            }
        } catch(const exception& e) {
            cout << "\nError :" << e.what();
            Utility::sleep(1000);
        }
    }
};

// ==================== COURSE MANAGEMENT ====================
class Course {
protected:
    string courseCode;
    string courseName;
    vector<string> lectureFiles;
    
public:
    Course(const string& code = "", const string& name = "") 
        : courseCode(code), courseName(name) {}
    
    virtual ~Course() = default;
    
    void addLectureFile(const string& filename) {
        lectureFiles.push_back(filename);
    }
    
    virtual void displayContent() {
        cout << "\n\tCourse: " << courseName << " (" << courseCode << ")" << endl;
        cout << "\tAvailable Materials:" << endl;
        for(size_t i = 0; i < lectureFiles.size(); i++) {
            cout << "\t" << (i + 1) << ". " << lectureFiles[i] << endl;
        }
    }
    
    void displayFileContent(const string& filename) {
        Utility::showLoading("Opening file");
        
        ifstream file(filename);
        if(file.is_open()) {
            string line;
            while(getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "\nError: Could not open file: " << filename << endl;
        }
    }
};

// ==================== LECTURE NOTES ====================
class LectureNote : public Course {
private:
    char selection;
    
public:
    LectureNote() {
        showAvailableCourses();
        getUserSelection();
        processSelection();
    }
    
private:
    void showAvailableCourses() {
        Utility::clearScreen();
        cout << "\t\t\t  =======================" << endl;
        cout << "\t\t\t  |    Lecture Notes    |" << endl;
        cout << "\t\t\t  =======================" << endl;
        cout << "\nAvailable Courses:" << endl;
        cout << "a) Object Oriented Programming" << endl;
        cout << "b) Communication Skills" << endl;
        cout << "c) Object Oriented Programming Lab" << endl;
        cout << "\nEnter your choice: ";
    }
    
    void getUserSelection() {
        cin >> selection;
        selection = tolower(selection);
    }
    
    void processSelection() {
        Utility::clearScreen();
        cout << "\t\t\t  =======================" << endl;
        cout << "\t\t\t  |    Lecture Content  |" << endl;
        cout << "\t\t\t  =======================" << endl;
        
        switch(selection) {
            case 'a':
                displayOOPContent();
                break;
            case 'b':
                displayCSContent();
                break;
            case 'c':
                displayOOPLabContent();
                break;
            default:
                cout << "Invalid selection!" << endl;
        }
    }
    
    void displayOOPContent() {
        cout << "\nLecture Title: Structure Code\n" << endl;
        displayFileContent(Config::COURSE_FILE_OOP);
    }
    
    void displayCSContent() {
        cout << "\nLecture Title: Letter Writing\n" << endl;
        displayFileContent(Config::COURSE_FILE_CS);
    }
    
    void displayOOPLabContent() {
        cout << "\nLecture Title: Static Data Members and Constants\n" << endl;
        displayFileContent(Config::COURSE_FILE_OOP_LAB);
    }
};

// ==================== ASSIGNMENT MANAGEMENT ====================
class AssignmentManager : public Course {
private:
    char courseSelection;
    char actionSelection;
    
public:
    AssignmentManager() {
        showAvailableCourses();
        getUserSelection();
        processAssignment();
    }
    
private:
    void showAvailableCourses() {
        Utility::clearScreen();
        cout << "\t\t\t  =======================" << endl;
        cout << "\t\t\t  |    Assignments      |" << endl;
        cout << "\t\t\t  =======================" << endl;
        cout << "\nAvailable Courses:" << endl;
        cout << "a) Object Oriented Programming" << endl;
        cout << "b) Communication Skills" << endl;
        cout << "\nEnter your choice: ";
        cin >> courseSelection;
        courseSelection = tolower(courseSelection);
    }
    
    void getUserSelection() {
        cout << "\n1) Download Assignment" << endl;
        cout << "2) Submit Assignment" << endl;
        cout << "Enter your choice: ";
        cin >> actionSelection;
    }
    
    void processAssignment() {
        if(actionSelection == '1') {
            downloadAssignment();
        } else if(actionSelection == '2') {
            submitAssignment();
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    void downloadAssignment() {
        Utility::showLoading("Downloading assignment");
        cout << "Download completed successfully!\n" << endl;
        
        // Display assignment content based on course
        if(courseSelection == 'a') {
            displayFileContent("D-ASS.txt");
        } else if(courseSelection == 'b') {
            displayFileContent("U-ASS.txt");
        }
    }
    
    void submitAssignment() {
        Utility::showLoading("Submitting assignment");
        cout << "Assignment submitted successfully!" << endl;
    }
};

// ==================== STUDENT CLASS ====================
class Student : public User {
private:
    string campus;
    
public:
    Student() : User() {
        authenticate();
    }
    
    void menu() override;
    
private:
    void authenticate();
    bool validateStudentId(const string& studentId);
    void displayTimeTable();
    void displayAttendance();
    void calculateGPA();
    void showLectureNotes();
    void showAssignments();
};

void Student::authenticate() {
    do {
        Utility::clearScreen();
        cout << "\t\t\t  =====================" << endl;
        cout << "\t\t\t  |   STUDENT LOGIN   |" << endl;
        cout << "\t\t\t  =====================" << endl;
        
        cout << "\n\tEnter Username (" << Config::STUDENT_USERNAME << "): ";
        cin >> name;
        cout << "\n\tEnter ID (Roll Number): ";
        cin >> id;
        
        if(Utility::toUpper(name) == Utility::toUpper(Config::STUDENT_USERNAME)) {
            if(validateStudentId(id)) {
                cout << "\n\tLogin Successful!" << endl;
                Utility::sleep(1000);
                return;
            } else {
                cout << "\n\tInvalid ID!" << endl;
            }
        } else {
            cout << "\n\tInvalid Credentials!" << endl;
        }
        
        Utility::sleep(1000);
    } while(true);
}

bool Student::validateStudentId(const string& studentId) {
    ifstream file(Config::STUDENT_RECORD_FILE);
    if(!file.is_open()) {
        cout << "\nError: Cannot access student records!" << endl;
        return false;
    }
    
    string line;
    while(getline(file, line)) {
        if(line.find(studentId) != string::npos) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}

void Student::menu() {
    char choice;
    char back;
    
    do {
        Utility::clearScreen();
        cout << "\t\t\t =====================" << endl;
        cout << "\t\t\t | Welcome Student   |" << endl;
        cout << "\t\t\t =====================" << endl;
        
        cout << "\nOptions:" << endl;
        cout << "a) Time Table" << endl;
        cout << "b) Attendance" << endl;
        cout << "c) GPA Calculator" << endl;
        cout << "d) Lecture Notes" << endl;
        cout << "e) Assignments" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        choice = tolower(choice);
        
        switch(choice) {
            case 'a': displayTimeTable(); break;
            case 'b': displayAttendance(); break;
            case 'c': calculateGPA(); break;
            case 'd': showLectureNotes(); break;
            case 'e': showAssignments(); break;
            default: cout << "Invalid choice!" << endl;
        }
        
        cout << "\nPress 'B' to go back to main menu: ";
        cin >> back;
    } while(toupper(back) == 'B');
}

void Student::displayTimeTable() {
    Utility::clearScreen();
    cout << "\t\t\t =====================" << endl;
    cout << "\t\t\t |    Time Table     |" << endl;
    cout << "\t\t\t =====================" << endl;
    
    cout << "\n" << string(100, '-') << endl;
    cout << setw(10) << "Time" << setw(15) << "Monday" << setw(20) << "Tuesday" 
         << setw(20) << "Wednesday" << setw(15) << "Thursday" << setw(10) << "Friday" << endl;
    cout << string(100, '-') << endl;
    
    // Sample timetable data
    vector<vector<string>> timetable = {
        {"8:30-9:25", "Comm Skills F5", "Discrete Math F4", "DLD F4", "DLD Lab", "-"},
        {"9:30-10:25", "OOP F3", "Comm Skills F4", "OOP F4", "Electronics Lab", "-"},
        {"10:30-11:25", "-", "OOP Lab SL-2", "-", "-", "-"},
        {"11:30-12:25", "-", "-", "Marketing F4", "DM F3", "Jumma Break"},
        {"12:30-1:25", "-", "-", "-", "POM B2", "-"}
    };
    
    for(const auto& row : timetable) {
        for(const auto& cell : row) {
            cout << setw(15) << cell;
        }
        cout << endl;
    }
}

void Student::displayAttendance() {
    Utility::clearScreen();
    cout << "\t\t\t =====================" << endl;
    cout << "\t\t\t |    Attendance     |" << endl;
    cout << "\t\t\t =====================" << endl;
    
    cout << "\n" << string(40, '-') << endl;
    cout << setw(30) << left << "Course" << setw(10) << "Attendance" << endl;
    cout << string(40, '-') << endl;
    
    // Sample attendance data
    vector<pair<string, string>> attendance = {
        {"Object Oriented Programming", "96%"},
        {"OOP Lab", "100%"},
        {"Digital Logic Design", "88%"},
        {"DLD Lab", "100%"},
        {"CIVICS", "98%"},
        {"Expository Writing", "75%"},
        {"Discrete Structures", "78%"}
    };
    
    for(const auto& record : attendance) {
        cout << setw(30) << left << record.first << setw(10) << record.second << endl;
    }
}

void Student::calculateGPA() {
    Utility::clearScreen();
    cout << "\t\t\t =======================" << endl;
    cout << "\t\t\t |   GPA Calculator    |" << endl;
    cout << "\t\t\t =======================" << endl;
    
    int numCourses;
    cout << "\nEnter number of courses: ";
    cin >> numCourses;
    
    double totalGradePoints = 0.0;
    
    for(int i = 0; i < numCourses; i++) {
        string courseName;
        double grade;
        
        cout << "\nEnter course " << (i + 1) << " name: ";
        cin.ignore();
        getline(cin, courseName);
        
        cout << "Enter grade for " << courseName << " (out of 4.0): ";
        cin >> grade;
        
        totalGradePoints += grade;
    }
    
    double gpa = totalGradePoints / numCourses;
    cout << fixed << setprecision(2);
    cout << "\nYour GPA: " << gpa << "/4.0" << endl;
}

void Student::showLectureNotes() {
    LectureNote notes;
}

void Student::showAssignments() {
    AssignmentManager assignments;
}

// ==================== TEACHER CLASS ====================
class Teacher : public User {
public:
    Teacher() : User() {
        authenticate();
    }
    
    void menu() override;
    
private:
    void authenticate();
    void uploadLectureNotes();
    void manageAssignments();
};

void Teacher::authenticate() {
    do {
        Utility::clearScreen();
        cout << "\t\t\t  =====================" << endl;
        cout << "\t\t\t  |   TEACHER LOGIN   |" << endl;
        cout << "\t\t\t  =====================" << endl;
        
        cout << "\n\tEnter Username: ";
        cin >> name;
        cout << "\n\tEnter ID: ";
        cin >> id;
        
        if(Utility::toUpper(name) == Utility::toUpper(Config::ADMIN_USERNAME) && id == to_string(Config::ADMIN_ID)) {
            cout << "\n\tLogin Successful!" << endl;
            Utility::sleep(1000);
            return;
        } else {
            cout << "\n\tInvalid Credentials! Try Again." << endl;
            Utility::sleep(1000);
        }
    } while(true);
}

void Teacher::menu() {
    char choice;
    char back;
    
    do {
        Utility::clearScreen();
        cout << "\t\t\t  =====================" << endl;
        cout << "\t\t\t  |  Welcome Teacher  |" << endl;
        cout << "\t\t\t  =====================" << endl;
        
        cout << "\nOptions:" << endl;
        cout << "a) Upload Lecture Notes" << endl;
        cout << "b) Manage Assignments" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        choice = tolower(choice);
        
        switch(choice) {
            case 'a': uploadLectureNotes(); break;
            case 'b': manageAssignments(); break;
            default: cout << "Invalid choice!" << endl;
        }
        
        cout << "\nPress 'B' to go back to main menu: ";
        cin >> back;
    } while(toupper(back) == 'B');
}

void Teacher::uploadLectureNotes() {
    Utility::clearScreen();
    cout << "\t\t\t  =======================" << endl;
    cout << "\t\t\t  |  Upload Lectures    |" << endl;
    cout << "\t\t\t  =======================" << endl;
    
    // Implementation for uploading lecture notes
    string course, filename, content;
    
    cout << "\nEnter course name: ";
    cin.ignore();
    getline(cin, course);
    
    cout << "Enter filename: ";
    getline(cin, filename);
    
    cout << "Enter lecture content (type 'END' on new line to finish):\n";
    ofstream file(filename);
    if(file.is_open()) {
        while(getline(cin, content) && content != "END") {
            file << content << endl;
        }
        file.close();
        cout << "Lecture notes saved successfully!" << endl;
    } else {
        cout << "Error saving lecture notes!" << endl;
    }
}

void Teacher::manageAssignments() {
    Utility::clearScreen();
    cout << "\t\t\t  =======================" << endl;
    cout << "\t\t\t  | Manage Assignments  |" << endl;
    cout << "\t\t\t  =======================" << endl;
    
    AssignmentManager assignments;
}

// ==================== ADMIN CLASS ====================
class Admin : public User {
private:
    static int recordCounter;
    
public:
    Admin() : User() {
        authenticate();
    }
    
    void menu() override;
    
private:
    void authenticate();
    void manageStudentRecords();
    void displayStudentRecords();
    void addStudentRecord();
};

int Admin::recordCounter = 0;

void Admin::authenticate() {
    do {
        Utility::clearScreen();
        cout << "\t\t\t  =====================" << endl;
        cout << "\t\t\t  |   ADMIN LOGIN     |" << endl;
        cout << "\t\t\t  =====================" << endl;
        
        cout << "\n\tEnter Username: ";
        cin >> name;
        
        string inputId;
        cout << "\n\tEnter ID: ";
        cin >> inputId;
        
        if(Utility::toUpper(name) == Utility::toUpper(Config::ADMIN_USERNAME) && inputId == to_string(Config::ADMIN_ID)) {
            cout << "\n\tLogin Successful!" << endl;
            Utility::sleep(1000);
            return;
        } else {
            cout << "\n\tInvalid Credentials! Try Again." << endl;
            Utility::sleep(1000);
        }
    } while(true);
}

void Admin::menu() {
    char choice;
    char back;
    
    do {
        Utility::clearScreen();
        cout << "\t\t\t =======================" << endl;
        cout << "\t\t\t |Welcome Administrator|" << endl;
        cout << "\t\t\t =======================" << endl;
        
        cout << "\nOptions:" << endl;
        cout << "a) Manage Student Records" << endl;
        cout << "b) Display Student Records" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        choice = tolower(choice);
        
        switch(choice) {
            case 'a': manageStudentRecords(); break;
            case 'b': displayStudentRecords(); break;
            default: cout << "Invalid choice!" << endl;
        }
        
        cout << "\nPress 'B' to go back to main menu: ";
        cin >> back;
    } while(toupper(back) == 'B');
}

void Admin::manageStudentRecords() {
    Utility::clearScreen();
    cout << "\t\t\t =======================" << endl;
    cout << "\t\t\t | Manage Student Records |" << endl;
    cout << "\t\t\t =======================" << endl;
    
    addStudentRecord();
}

void Admin::addStudentRecord() {
    string studentId, firstName, lastName;
    
    cout << "\nEnter Student ID: ";
    cin >> studentId;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    
    ofstream file(Config::STUDENT_RECORD_FILE, ios::app);
    if(file.is_open()) {
        file << studentId << " " << firstName << " " << lastName << endl;
        file.close();
        Utility::showLoading("Saving record");
        cout << "Student record saved successfully!" << endl;
    } else {
        cout << "Error: Could not save student record!" << endl;
    }
}

void Admin::displayStudentRecords() {
    Utility::clearScreen();
    cout << "\t\t\t =======================" << endl;
    cout << "\t\t\t | Student Records     |" << endl;
    cout << "\t\t\t =======================" << endl;
    
    Utility::showLoading("Loading records");
    
    ifstream file(Config::STUDENT_RECORD_FILE);
    if(file.is_open()) {
        string line;
        int studentCount = 0;
        
        cout << "\n" << string(50, '=') << endl;
        while(getline(file, line)) {
            studentCount++;
            cout << "Student #" << studentCount << ":\n";
            cout << "Record: " << line << endl;
            cout << string(50, '-') << endl;
        }
        file.close();
        
        if(studentCount == 0) {
            cout << "No student records found!" << endl;
        }
    } else {
        cout << "Error: Could not open student records file!" << endl;
    }
}

// ==================== MAIN APPLICATION ====================
class LearningManagementSystem {
private:
    unique_ptr<Developer> developerInfo;
    unique_ptr<University> university;
    
public:
    LearningManagementSystem() {
        initializeSystem();
    }
    
    void run() {
        showDeveloperInfo();
        showUniversityInfo();
        mainMenu();
    }
    
private:
    void initializeSystem() {
        developerInfo = make_unique<SubDeveloper>();
        university = make_unique<University>();
    }
    
    void showDeveloperInfo() {
        developerInfo->display();
        Utility::pressAnyKeyToContinue();
        Utility::clearScreen();
    }
    
    void showUniversityInfo() {
        // University info is already shown in constructor
        Utility::clearScreen();
    }
    
    void mainMenu() {
        char back;
        
        do {
            Utility::clearScreen();
            cout << "\t\t\t =======================" << endl;
            cout << "\t\t\t |   MAIN MENU         |" << endl;
            cout << "\t\t\t =======================" << endl;
            
            cout << "\nSelect User Type:" << endl;
            cout << "1) Administrator" << endl;
            cout << "2) Teacher" << endl;
            cout << "3) Student" << endl;
            cout << "4) Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            
            int choice;
            cin >> choice;
            
            processUserChoice(choice);
            
            if(choice != 4) {
                cout << "\nPress 'T' to return to main menu or any other key to exit: ";
                cin >> back;
            } else {
                back = 'E';
            }
            
        } while(toupper(back) == 'T');
        
        cout << "\nThank you for using Learning Management System!" << endl;
    }
    
    void processUserChoice(int choice) {
        Utility::clearScreen();
        
        switch(choice) {
            case 1: {
                Admin admin;
                admin.menu();
                break;
            }
            case 2: {
                Teacher teacher;
                teacher.menu();
                break;
            }
            case 3: {
                Student student;
                student.menu();
                break;
            }
            case 4:
                cout << "Exiting system..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    try {
        LearningManagementSystem lms;
        lms.run();
    } catch(const exception& e) {
        cerr << "System Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
#include <iostream>
#include <map>
#include <list>
#include <string>
using namespace std;

class Section;
class Course;
class ScheduleofClasses;

class Person;
class Student;
class Professor;

class TranscriptEntry;
class Transcript;

/* ------------------------------------------------------ */
class Course
{
    string courseNo;
    string courseName;
    int credits;
    map<string, Course *> preRequisites;
    map<string, Section *> sections;

public:
    // Constructors
    Course();           // Default constructor
    Course(string courseNo, string courseName, int credits);
    // Setters
    void setCourseNo(string courseNo);
    void setCourseName(string courseName);
    void setCredits(int credits);
    // Getters
    string getCourseNo();
    string getCourseName();
    int getCredits();
    // Methods
    Section *scheduleSection(string sectionNo, string dayOfWeek, string timeOfDay, string room, int seatingCapacity);
    void addPreRequisite(Course *course);
    bool hasPreRequisites(Course *course);
    // Display
    void displayCourseInfo();
    // Destructor
    ~Course();
};

/* ------------------------------------------------------ */
class Section
{
    string sectionNo;
    string dayofWeek;
    string timeofDay;
    string room;
    int seatingCapacity;
    Course *course;

public:
    // Constructors
    Section();         // Default constructor   
    Section(string sectionNo, string dayofWeek, string timeofDay, string room, int seatingCapacity);
    
    // Setters
    void setSectionNo(string sectionNo);
    void setDayofWeek(string dayofWeek);
    void setTimeofDay(string timeofDay);
    void setRoom(string room);
    void setSeatingCapacity(int seatingCapacity);
    void setCourse(Course *course);
    // Getters
    string getSectionNo();
    string getDayofWeek();
    string getTimeofDay();
    string getRoom();
    Course *getCourse();
    int getSeatingCapacity();
    // Methods
    void enroll(); // Placeholder, as Student is undefined
    void drop();   // Placeholder, as Student is undefined
    void postGrades();
    void confirmSeatAvailability();
    // Display
    void displaySectionInfo();
};

/* ------------------------------------------------------ */
class ScheduleofClasses
{
    string semester;
    map<string, Section> sections;

public:
    // Constructors
    ScheduleofClasses(string semester);
    // Setters
    void setSemester(string semester);
    void setSections(Section *section);
    // Getters
    string getSemester();
    Section *findSection(string sectionNo);
    // Display
    void displaySchedule();
};

/* ------------------------------------------------------ */
class Person
{
    string ssn;
    string name;
public:
    // Constructors
    Person() ;
    Person(string ssn, string name);
    // Setters
    void setSSN(string ssn);
    void setName(string name);
    // Getters
    string getSSN();
    string getName();
    // Display
    void displayPersonInfo();
};

/* ------------------------------------------------------ */
class Student : public Person
{
    string degree;
    string major;
public:
    // Constructors
    Student() ;
    Student(string ssn, string name, string degree, string major);
    // Setters
    void setDegree(string degree);
    void setMajor(string major);
    // Getters
    string getDegree();
    string getMajor();
    // Methods
    void addSection(Section *section);
    void dropSection(Section *section);
    void isEnrolled(Section *section);
    // Display
    void displayStudentInfo();
};

/* ------------------------------------------------------ */
class Professor : public Person
{
    string title;
    string department;
public:
    // Constructors
    Professor() ;
    Professor(string ssn, string name, string title, string department);
    // Setters
    void setTitle(string title);
    void setDepartment(string department);
    // Getters
    string getTitle();
    string getDepartment();
    // Methods
    void agreeToTeach(Section *section);
    // Display
    void displayProfessorInfo();
};

/* ------------------------------------------------------ */

/*-----------------------COURSE FUNCTION-------------------------- */
// Setters
void Course::setCourseNo(string courseNo) { this->courseNo = courseNo; }
void Course::setCourseName(string courseName) { this->courseName = courseName; }
void Course::setCredits(int credits) { this->credits = credits; }
// Getters
string Course::getCourseNo() { return courseNo; }
string Course::getCourseName() { return courseName; }
int Course::getCredits() { return credits; }
// Methods
Section *Course::scheduleSection(string sectionNo, string dayOfWeek, string timeOfDay, string room, int seatingCapacity)
{
    // Schedule a section for the course
    Section *newSection = new Section(sectionNo, dayOfWeek, timeOfDay, room, seatingCapacity);
    newSection->setCourse(this); // Set the course for the section
    sections[sectionNo] = newSection;
    return newSection;
}
void Course::addPreRequisite(Course *course)
{
    preRequisites[course->getCourseNo()] = course;
}
bool Course::hasPreRequisites(Course *course)
{
    // Check if the course has pre-requisites
    return preRequisites.find(course->getCourseNo()) != preRequisites.end();
}
// Display
void Course::displayCourseInfo()
{
    cout << "Course No: " << courseNo << endl;
    cout << "Course Name: " << courseName << endl;
    cout << "Credits: " << credits << endl;
    cout << "Pre-Requisites: ";
    for (auto preReq : preRequisites)
    {
        cout << preReq.second->getCourseNo() << " ";
    }
    cout << endl;
}
// Constructors
Course::Course()
{
    this->courseNo = "";
    this->courseName = "";
    this->credits = 0;
}
Course::Course(string courseNo, string courseName, int credits)
{
    setCourseNo(courseNo);
    setCourseName(courseName);
    setCredits(credits);
}
// Destructor
Course::~Course()
{
    for (auto &i : this->sections)
    {
        delete i.second;
    }
}

/*-----------------------SECTION FUNCTION------------------------- */
// Setters
void Section::setSectionNo(string sectionNo) { this->sectionNo = sectionNo; }
void Section::setDayofWeek(string dayofWeek) { this->dayofWeek = dayofWeek; }
void Section::setTimeofDay(string timeofDay) { this->timeofDay = timeofDay; }
void Section::setRoom(string room) { this->room = room; }
void Section::setSeatingCapacity(int seatingCapacity) { this->seatingCapacity = seatingCapacity; }
void Section::setCourse(Course *course) { this->course = course; }
// Getters
string Section::getSectionNo() { return sectionNo; }
string Section::getDayofWeek() { return dayofWeek; }
string Section::getTimeofDay() { return timeofDay; }
string Section::getRoom() { return room; }
Course *Section::getCourse() { return course; }
int Section::getSeatingCapacity() { return seatingCapacity; }
// Methods
void Section::enroll() { /* Enroll student in the section (placeholder) */ }
void Section::drop() { /* Drop student from the section (placeholder) */ }
void Section::postGrades() { /* Post grades for the section */ }
void Section::confirmSeatAvailability() { /* Confirm seat availability for the section */ }
// Display
void Section::displaySectionInfo()
{
    cout << "Section No: " << sectionNo << endl;
    cout << "Day of Week: " << dayofWeek << endl;
    cout << "Time of Day: " << timeofDay << endl;
    cout << "Room: " << room << endl;
    cout << "Seating Capacity: " << seatingCapacity << endl;
    cout << "-------------------------" << endl;
}
// Constructors
Section::Section()
{
    this->sectionNo = "";
    this->dayofWeek = "";
    this->timeofDay = "";
    this->room = "";
    this->seatingCapacity = 0;
}
Section::Section(string sectionNo, string dayofWeek, string timeOfDay, string room, int seatingCapacity)
{
    setSectionNo(sectionNo);
    setDayofWeek(dayofWeek);
    setTimeofDay(timeOfDay);
    setRoom(room);
    setSeatingCapacity(seatingCapacity);
}

/*-----------------------SCHEDULE OF CLASSES FUNCTION------------- */
// Setters
void ScheduleofClasses::setSemester(string semester) { this->semester = semester; }
void ScheduleofClasses::setSections(Section *section) { this->sections[section->getSectionNo()] = *section; }
// Getters
string ScheduleofClasses::getSemester() { return this->semester; }
Section *ScheduleofClasses::findSection(string sectionNo)
{
    // Find a section by its number
    if (sections.find(sectionNo) != sections.end())
    {
        return &sections[sectionNo];
    }
    else
    {
        cout << "Section not found." << endl;
        return nullptr;
    }
}
// Display
void ScheduleofClasses::displaySchedule()
{
    cout << "Schedule of Classes for Semester: " << semester << endl;
    cout << endl;
    cout << "----------------------------------------" << endl;
    for (auto &section : sections)
    {
        section.second.displaySectionInfo();
    }
}
// Constructors
ScheduleofClasses::ScheduleofClasses(string semester) { setSemester(semester); }

/*-----------------------PERSON FUNCTION-------------------------- */
// Setters
void Person::setSSN(string ssn) { this->ssn = ssn; }
void Person::setName(string name) { this->name = name; }
// Getters
string Person::getSSN() { return ssn; }
string Person::getName() { return name; }
// Display
void Person::displayPersonInfo()
{
    cout << "SSN: " << ssn << endl;
    cout << "Name: " << name << endl;
}
// Constructors
Person::Person()
{
    this->ssn = "";
    this->name = "";
}
Person::Person(string ssn, string name)
{
    setSSN(ssn);
    setName(name);
}
/*-----------------------STUDENT FUNCTION------------------------ */
// Setters
void Student::setDegree(string degree) { this->degree = degree; }
void Student::setMajor(string major) { this->major = major; }
// Getters
string Student::getDegree() { return degree; }
string Student::getMajor() { return major; }
// Methods
void Student::addSection(Section *section) { /* Add section to student's schedule (placeholder) */ }
void Student::dropSection(Section *section) { /* Drop section from student's schedule (placeholder) */ }
void Student::isEnrolled(Section *section) { /* Check if student is enrolled in the section (placeholder) */ }
// Display
void Student::displayStudentInfo()
{
    cout << "Degree: " << degree << endl;
    cout << "Major: " << major << endl;
}
// Constructors
Student::Student()
{
    this->degree = "";
    this->major = "";
}
Student::Student(string ssn, string name, string degree, string major) : Person(ssn, name)
{
    setDegree(degree);
    setMajor(major);
}
/*-----------------------PROFESSOR FUNCTION--------------------- */
// Setters
void Professor::setTitle(string title) { this->title = title; }
void Professor::setDepartment(string department) { this->department = department; }
// Getters
string Professor::getTitle() { return title; }
string Professor::getDepartment() { return department; }
// Methods
void Professor::agreeToTeach(Section *section) { /* Agree to teach the section (placeholder) */ }
// Display
void Professor::displayProfessorInfo()
{
    cout << "Title: " << title << endl;
    cout << "Department: " << department << endl;
}
// Constructors
Professor::Professor()
{
    this->title = "";
    this->department = "";
}
Professor::Professor(string ssn, string name, string title, string department) : Person(ssn, name)
{
    setTitle(title);
    setDepartment(department);
}


/* ----------------------MAIN---------------------------- */
int main()
{
    // Create Courses
    Course *OOP = new Course("MTH10407", "OOP", 4);
    Course *DSA = new Course("MTH10405", "DSA", 4);
    Course *CSDL = new Course("MTH10312", "CSDL", 4);

    // Schedule Sections: 
    // Schedule Sections for OOP
    Section *KDL1_23_24 = OOP->scheduleSection("MTH10407-23-24-3", "Tue", "8:00AM", "F-202", 60);
    Section *TTH1_23_24 = OOP->scheduleSection("MTH10407-23-24-4", "Wed", "8:00AM", "E-203", 60);
    // Schedule Sections for DSA
    Section *KDL2_23_24 = DSA->scheduleSection("MTH10405-23-24-3", "Wed", "8:00AM", "E-202", 60);
    Section *TTH2_23_24 = DSA->scheduleSection("MTH10405-23-24-4", "Fri", "8:00AM", "E-203", 60);
    // Schedule Sections for CSDL
    Section *TTH_23_24 = CSDL->scheduleSection("MTH10312-23-24-3", "Fri", "9:45AM", "E-202", 60);

    // Schedule of Classes
    ScheduleofClasses *HKI = new ScheduleofClasses("HKI-2023-2024");
    HKI->setSections(KDL1_23_24);
    HKI->setSections(TTH1_23_24);
    HKI->setSections(KDL2_23_24);
    HKI->setSections(TTH2_23_24);
    HKI->setSections(TTH_23_24);

    // Display Course Information
    HKI->displaySchedule();

    // Add Pre-requisites
    OOP->addPreRequisite(DSA);
    OOP->addPreRequisite(CSDL);

    DSA->addPreRequisite(CSDL);

    // Has Pre-requisites
    cout << "Does OOP have DSA as a pre-requisite? " << (OOP->hasPreRequisites(DSA) ? "Yes" : "No") << endl;
    cout << "Does DSA have CSDL as a pre-requisite? " << (DSA->hasPreRequisites(CSDL) ? "Yes" : "No") << endl;

    // Find Section
    cout << "Searching for Section: MTH10407-23-24-3" << endl;
    cout << "----------------------------------------" << endl;
    Section *foundSection = HKI->findSection("MTH10405-23-24-4");
    if (foundSection) {
        cout << "Found Section: " << foundSection->getSectionNo() << endl;
        foundSection->displaySectionInfo();
    } else {
        cout << "Section not found." << endl;
    }

    // Delete:
    delete OOP;
    delete DSA;
    delete CSDL;
    delete HKI;
    return 0;
}
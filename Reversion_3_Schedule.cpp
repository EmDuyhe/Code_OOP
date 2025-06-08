#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Employee;
class Teacher;
class Manager;

class Course;
class Section;
class Studyroom;

class Schedule;

/*-------------------------------------------------------------*/
class Employee
{
    string name;

public:
    // Constructor
    Employee(string employeeName);
    // Setters
    void setName(string employeeName);
    // Getters
    string getName() ;
    // Display
    virtual void display();
};

class Teacher : public Employee
{
    string Faculty;
    Schedule *schedule;

public:
    // Constructor
    Teacher(string teacherName, string faculty);
    // Setters
    void setFaculty(string faculty);
    void setSchedule(Schedule *newSchedule);
    // Getters
    string getFaculty();
    Schedule *getSchedule();
    // Methods
    void takeSchedule(Schedule *newSchedule);
    // Display
    void display() override;
};

class Manager : public Employee
{
public:
    // Constructor
    Manager(string managerName);
    // Display
    void display() override;
};

/*----------------*/
class Course
{
    string courseName;
    string courseCode;

public:
    // Constructor
    Course(string name, string code);
    // Setters
    void setCourseName(string name);
    void setCourseCode(string code);
    // Getters
    string getCourseName() const;
    string getCourseCode() const;
    // Display
    void display();
};

class Section
{
    string timeOfSection;
    Course *course;
    Studyroom *studyroom;

public:
    // Constructor
    Section(string time);
    // Setters
    void setTimeOfSection(string time);
    void setCourse(Course *course);
    void setStudyroom(Studyroom *room);
    // Getters
    string getTimeOfSection();
    Course *getCourse();
    Studyroom *getStudyroom();
    // Methods
    void assignRoom(Studyroom *room);
    // Display
    void display();
};

class Studyroom
{
    string roomName;
    int seatsNumber;

public:
    // Constructor
    Studyroom(string name, int number);
    // Setters
    void setRoomName(string name);
    void setSeatsNumber(int number);
    // Getters
    string getRoomName();
    int getSeatsNumber();
    // Display
    void display();
};

/*----------------*/
class Schedule
{
    vector<Section *> sections;
    Teacher *teacher;

public:
    // Constructor
    Schedule(Teacher *teacher);
    // Setters
    void setTeacher(Teacher *newTeacher);
    // Getters
    vector<Section *> getSections();
    Teacher *getTeacher();
    // Methods
    void addSectionToSchedule(Section *section);
    void removeSectionFromSchedule(Section *section);
    // Display
    void display();
};
/*-------------------------------------------------------------*/
// Employee:
// Setters
void Employee::setName(string employeeName) {
    name = employeeName;
}
// Getters
string Employee::getName() {
    return name;
}
// Display
void Employee::display() {
    cout << "Employee Name: " << getName() << endl;
}
// Constructor
Employee::Employee(string employeeName){
    setName(employeeName);
};

// Teacher:
// Setters
void Teacher::setFaculty(string faculty) {
    Faculty = faculty;
}
void Teacher::setSchedule(Schedule *newSchedule) {
    schedule = newSchedule;
}
// Getters
string Teacher::getFaculty() {
    return Faculty;
}
Schedule *Teacher::getSchedule() {
    return schedule;
}
// Methods
void Teacher::takeSchedule(Schedule *newSchedule) {
    setSchedule(newSchedule);
}
// Display
void Teacher::display() {
    cout << "Teacher Name: " << getName() << ", Faculty: " << getFaculty() << endl;
}
// Constructor
Teacher::Teacher(string teacherName, string faculty) : Employee(teacherName){
    setFaculty(faculty);
    schedule = nullptr; 
}

// Manager:
// Display
void Manager::display() {
    cout << "Manager Name: " << getName() << endl;
}
// Constructor
Manager::Manager(string managerName) : Employee(managerName) {
}

// Course:
// Setters
void Course::setCourseName(string name) {
    courseName = name;
}
void Course::setCourseCode(string code) {
    courseCode = code;
}
// Getters
string Course::getCourseName() const {
    return courseName;
}
string Course::getCourseCode() const {
    return courseCode;
}
// Display
void Course::display() {
    cout << "Course Name: " << getCourseName() << endl;
    cout << "Course Code: " << getCourseCode() << endl;
}
// Constructor
Course::Course(string name, string code) {
    setCourseName(name);
    setCourseCode(code);
}

// Section:
// Setters
void Section::setTimeOfSection(string time) {
    timeOfSection = time;
}
void Section::setCourse(Course *course) {
    this->course = course;
}   
void Section::setStudyroom(Studyroom *room) {
    studyroom = room;
}
// Getters
string Section::getTimeOfSection() {
    return timeOfSection;
}
Course *Section::getCourse() {
    return course;
}
Studyroom *Section::getStudyroom() {
    return studyroom;
}
// Methods
void Section::assignRoom(Studyroom *room) {
    setStudyroom(room);
}
// Display
void Section::display() {
    cout << "Section Time: " << getTimeOfSection() << ", Course: ";
    if (getCourse()) {
        getCourse()->display();
    } 
    if (getStudyroom()) {
        getStudyroom()->display();
    }
}
// Constructor
Section::Section(string time) {
    setTimeOfSection(time);
}

// Studyroom:
// Setters
void Studyroom::setRoomName(string name) {
    roomName = name;
}
void Studyroom::setSeatsNumber(int number) {
    seatsNumber = number;
}
// Getters
string Studyroom::getRoomName() {
    return roomName;
}
int Studyroom::getSeatsNumber() {
    return seatsNumber;
}
// Display
void Studyroom::display() {
    cout << "Studyroom Name: " << getRoomName() << endl;
    cout << "Seats Number: " << getSeatsNumber() << endl;
}
// Constructor
Studyroom::Studyroom(string name, int number) {
    setRoomName(name);
    setSeatsNumber(number);
}

// Schedule:
// Setters
void Schedule::setTeacher(Teacher *newTeacher) {
    teacher = newTeacher;
}
// Getters
vector<Section *> Schedule::getSections() {
    return sections;
}
Teacher *Schedule::getTeacher() {
    return teacher;
}
// Methods
void Schedule::addSectionToSchedule(Section *section) {
    sections.push_back(section);
}
void Schedule::removeSectionFromSchedule(Section *section) {
    sections.erase(remove(sections.begin(), sections.end(), section), sections.end());
}
// Display
void Schedule::display() {
    cout << endl;
    cout << "Schedule for Teacher: " << (getTeacher() ? getTeacher()->getName() : "No Teacher Assigned") << endl;
    for (const auto &section : sections) {
        section->display();
        cout << endl;
    }
}
// Constructor
Schedule::Schedule(Teacher *teacher) {
    setTeacher(teacher);
}


/*-------------------------------------------------------------*/
int main()
{
    // Danh sách giáo viên
    vector<Teacher*> teachers;
    teachers.push_back(new Teacher("Alice", "Toán - Tin học"));
    teachers.push_back(new Teacher("Bob", "Công nghệ thông tin"));

    // Danh sách môn học
    vector<Course*> courses;
    courses.push_back(new Course("DSA", "MTH10405"));
    courses.push_back(new Course("OOP", "MTH10407"));
    courses.push_back(new Course("AI", "MTH20410"));

    // Danh sách phòng học
    vector<Studyroom*> rooms;
    rooms.push_back(new Studyroom("C204", 40));
    rooms.push_back(new Studyroom("B101", 50));

    // Tạo thời khóa biểu cho Alice
    Schedule* aliceSchedule = new Schedule(teachers[0]);
    teachers[0]->setSchedule(aliceSchedule);

    // Lớp học 1: Alice - DSA tại C204 - Thứ 3
    Section* s1 = new Section("2023-2024-HK2-Tue");
    s1->setCourse(courses[0]);
    s1->setStudyroom(rooms[0]);
    aliceSchedule->addSectionToSchedule(s1);

    // Lớp học 2: Alice - OOP tại C204 - Thứ 4
    Section* s2 = new Section("2023-2024-HK2-Wed");
    s2->setCourse(courses[1]);
    s2->setStudyroom(rooms[0]);
    aliceSchedule->addSectionToSchedule(s2);

    // Tạo thời khóa biểu cho Bob
    Schedule* bobSchedule = new Schedule(teachers[1]);
    teachers[1]->setSchedule(bobSchedule);

    // Lớp học 3: Bob - AI tại B101 - Thứ 2
    Section* s3 = new Section("2023-2024-HK2-Mon");
    s3->setCourse(courses[2]);
    s3->setStudyroom(rooms[1]);
    bobSchedule->addSectionToSchedule(s3);

    // In thông tin giáo viên và thời khóa biểu
    cout << "=========== Thong Tin Giao Vien & Thoi Khoa Bieu ===========" << endl;
    for (Teacher* teacher : teachers)
    {
        teacher->display();
        if (teacher->getSchedule())
        {
            teacher->getSchedule()->display();
        }
        cout << "------------------------------------------------------------" << endl;
    }

    // Cleanup (có thể thay bằng smart pointer sau này)
    for (Teacher* t : teachers) delete t;
    for (Course* c : courses) delete c;
    for (Studyroom* r : rooms) delete r;
    delete s1;
    delete s2;
    delete s3;
    delete aliceSchedule;
    delete bobSchedule;

    return 0;
}

#include <iostream>
#include <list>
#include <string>
using namespace std;

class Student;
class Professor;
/*----------------------------------*/
class Student
{
    string id;
    string name;
    list<Professor *> Professors;

public:
    // Constructor
    Student(string theID, string theName);
    // Setter
    void setid(string value);
    void setname(string value);
    void addProfessors(Professor *professors);
    // Getter
    string getid();
    string getname();
    list<Professor *> getProfessors();
    // Methods
    void attachProfessor(Professor *Professor);
    void detachProfessor(Professor *professors);
    // Display
    void display_Student();
};

class Professor
{
    string name;
    list<Student *> Students;

public:
    // Constructor
    Professor(string theName);
    // Setter
    void setname(string value);
    void addStudents(Student *student);
    // Getter
    string getname();
    list<Student *> getStudents();
    // Methods
    void attachStudent(Student *student);
    void detachStudent(Student *student);
    void detachAll_A();
    // Display
    void display_Professor();
};
/*-------------------------------------*/

void Student::setid(string val1)
{
    this->id = val1;
}
void Student::setname(string val2)
{
    this->name = val2;
}
void Student::addProfessors(Professor *professors)
{
    this->Professors.push_back(professors);
}

string Student::getid()
{
    return this->id;
}
string Student::getname()
{
    return this->name;
}

list<Professor *> Student::getProfessors()
{
    return this->Professors;
}

void Student::display_Student()
{
    cout << "The ID : " << this->getid() << endl;
    cout << "The Name : " << this->getname() << endl;
    cout << "The Professor: " << endl;
    for(auto i:this->Professors){
        i->display_Professor();
    }
}

Student::Student(string name, string id)
{
    this->setid(id);
    this->setname(name);
}
/*--------------------------------*/
void Professor::setname(string name)
{
    this->name = name;
}

void Professor::addStudents(Student *student)
{
    this->Students.push_back(student);
}

string Professor::getname()
{
    return this->name;
}

list<Student *> Professor::getStudents()
{
    return this->Students;
}

void Professor::display_Professor()
{
    cout << "The Name: " << this->getname() <<endl;
}

Professor::Professor(string theName)
{
    this->setname(theName);
}
/*-------------------------*/
void Student::attachProfessor(Professor *professor)
{
    for (auto tmp : this->Professors)
    {
        if (tmp == professor)
        {
            return;
        }
    }
    this->addProfessors(professor);
    professor->attachStudent(this);
}
void Professor::attachStudent(Student *student)
{
    for (auto tmp : this->Students)
    {
        if (tmp == student)
        {
            return;
        }
    }
    this->addStudents(student);
}

/*-------------------------*/
void Student::detachProfessor(Professor *professors)
{
    for (auto i = Professors.begin(); i != Professors.end();)
    {
        Professor *pr = *i;
        i = Professors.erase(i);
        pr->detachStudent(this);
    }
}
void Professor::detachStudent(Student *student)
{
    this->Students.remove(student);
}

void Professor::detachAll_A()
{
    for (Student *st : this->getStudents())
    {
        st->detachProfessor(this);
    }
};
/*-------------------------*/
int main(){
    Student student_1("23110143","Duy");
    Student student_2("23110154","Hieu");
    Student student_3("23110111","Thinh");

    Professor professor_1("Thao");
    Professor professor_2("Luong");

    student_1.attachProfessor(&professor_1);
    student_1.attachProfessor(&professor_2);

    student_2.attachProfessor(&professor_1);
    student_2.attachProfessor(&professor_2);
    
    student_3.attachProfessor(&professor_2);

    student_1.display_Student();
    student_2.display_Student();
    student_3.display_Student();

    return 0;
}
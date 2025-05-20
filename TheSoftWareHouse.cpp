#include <iostream>
#include <string>
#include <list>
#include <map>
using namespace std;

/*----------------------------------------------------------------*/
// The Employee class represents a general employee with attributes
// such as number, name, and salary. It provides methods to set and
// get these attributes, as well as a method to display the employee's details.
class Employee
{
private:
    string payrollNumber; // Employee's payroll number
    double monthlySalary; // Employee's monthly salary
    string name;          // Employee's name

public:
    // Constructor
    Employee(string payrollNumber, double monthlySalary, string name);
    // Setters
    void setPayrollNumber(string payrollNumber);
    void setMonthlySalary(double monthlySalary);
    void setName(string name);
    // Getters
    string getPayrollNumber();
    double getMonthlySalary();
    string getName();
    // Display method
    virtual void display();
    virtual ~Employee() {}
};
// Employee class method definitions
// Constructor
Employee::Employee(string payrollNumber, double monthlySalary, string name)
{
    this->payrollNumber = payrollNumber;
    this->monthlySalary = monthlySalary;
    this->name = name;
}

// Setters
void Employee::setPayrollNumber(string payrollNumber)
{
    this->payrollNumber = payrollNumber;
}
void Employee::setMonthlySalary(double monthlySalary)
{
    this->monthlySalary = monthlySalary;
}
void Employee::setName(string name)
{
    this->name = name;
}
// Getters
string Employee::getPayrollNumber()
{
    return this->payrollNumber;
}
double Employee::getMonthlySalary()
{
    return this->monthlySalary;
}
string Employee::getName()
{
    return this->name;
}

// Display method
void Employee::display()
{
    cout << "Payroll Number: " << getPayrollNumber() << endl;
    cout << "Name          : " << getName() << endl;
    cout << "Monthly Salary: " << getMonthlySalary() << endl;
}
/*----------------------------------------------------------------*/
// The Programmer class inherits from the Employee class and adds
// an additional attribute, language, which represents the programming
// language the programmer specializes in. It overrides the display
// method to include the language information.
class Programmer : public Employee
{
private:
    string language; // Programming language specialization

public:
    // Constructor
    Programmer(string payrollNumber, string name, double monthlySalary, string language);
    // Setters
    void setLanguage(string language);
    // Getters
    string getLanguage();
    // Display method
    void display();
};
// Programmer class method definitions
// Constructor
Programmer::Programmer(string payrollNumber, string name, double monthlySalary, string language)
    : Employee(payrollNumber, monthlySalary, name)
{
    this->language = language;
}
// Setters
void Programmer::setLanguage(string language)
{
    this->language = language;
}
// Getters
string Programmer::getLanguage()
{
    return this->language;
}
// Display method
void Programmer::display()
{
    Employee::display();
    cout << "Programming Language: " << getLanguage() << endl;
}

/*----------------------------------------------------------------*/
// The ProjectLeader class inherits from the Programmer class and
// manages a list of programmers. It overrides the display method
// to include the list of programmers it manages.
class ProjectLeader : public Programmer
{
private:
    list<Programmer *> programmers; // List of programmers managed by the project leader
public:
    // Constructor
    ProjectLeader(string payrollNumber, string name, double monthlySalary, string language);
    // Setters
    void setProgrammers(list<Programmer *> programmers);
    // Getters
    list<Programmer *> getProgrammers();
    
    // Access methods
    void addProgrammer(Programmer *p);
    void removeProgrammer(Programmer *p);
    
    // Display method
    void displayProgrammers();
    void display();
};
// ProjectLeader class method definitions
// Constructor
ProjectLeader::ProjectLeader(string payrollNumber, string name, double monthlySalary, string language)
    : Programmer(payrollNumber, name, monthlySalary, language)
{
}
// Setters
void ProjectLeader::setProgrammers(list<Programmer *> programmers)
{
    this->programmers = programmers;
}
// Getters
list<Programmer *> ProjectLeader::getProgrammers()
{
    return this->programmers;
}

// Access methods
// Add a programmer to the list
void ProjectLeader::addProgrammer(Programmer *p)
{
    programmers.push_back(p);
}
// Remove a programmer from the list
void ProjectLeader::removeProgrammer(Programmer *p)
{
    programmers.remove(p);
}

// Display the list of programmers managed by the project leader
void ProjectLeader::displayProgrammers()
{
    cout << "--------------------------------------------------" << endl;
    cout << "Project Leader's Programmerc: " << endl;
    for (auto p : programmers)
    {
        p->display();
        cout << endl;
    }
}

void ProjectLeader::display()
{
    Programmer::display();
    displayProgrammers();
}
/*----------------------------------------------------------------*/
// The SoftwareHouse class represents a software company. It has a name
// and a list of programmers who work for the company. It provides methods
// to set the name, add programmers to the list, and display the details
// of the software house and its programmers.
class SoftwareHouse
{
private:
    string theName;                      // Name of the software house
    map<string, Employee *> theStaff;    // Map of employees with their payroll numbers

public:
    // Constructor
    SoftwareHouse(string name);
    // Setters
    void setName(string name);
    // Getters
    string getClassName();
    // Access methods
    void addStaff(Employee *employee);
    // Display methods
    void displayProjectLeaders();
    void displayStaff();
    void display();
};
// SoftwareHouse class method definitions
// Constructor
SoftwareHouse::SoftwareHouse(string name)
{
    this->theName = name;
}
// Setters
void SoftwareHouse::setName(string name)
{
    this->theName = name;
}
// Getters
string SoftwareHouse::getClassName()
{
    return this->theName;
}

// Add an employee to the staff
// If the employee already exists, display a message
// If the employee does not exist, add them to the staff
// and display a message
void SoftwareHouse::addStaff(Employee *employee)
{
    string payrollNumber = employee->getPayrollNumber();
    if (theStaff.find(payrollNumber) != theStaff.end())
    {
        cout << "Employee with payroll number " << payrollNumber << " is already in the staff!" << endl;
    }
    else
    {
        theStaff[payrollNumber] = employee;
        cout << "Employee: " << employee->getName() << " added to the staff." << endl;
    }
}

// Display the staff of the software house

void SoftwareHouse::displayStaff()
{
    if (theStaff.empty())
    {
        cout << "\tNo staff available." << endl;
    }
    else
    {
        for (auto &entry : theStaff)
        {
            cout << "\tPayroll Number: " << entry.first << endl;

            // Check if the staff is a ProjectLeader
            ProjectLeader *pl = dynamic_cast<ProjectLeader *>(entry.second);
            if (pl)
            {
                cout << "\tRole: Project Leader" << endl;
                pl->display(); // Call ProjectLeader's display method
            }
            else
            {
                cout << "\tRole: Programmer" << endl;
                entry.second->display(); // Call Employee's or Programmer's display method
            }
            cout << endl;
        }
    }
}
// Display only Project Leaders in the software house

void SoftwareHouse::displayProjectLeaders()
{
    cout << "--------------------------------------------------" << endl;
    cout << "Project Leaders:" << endl;
    for (auto &entry : theStaff)
    {
        ProjectLeader *pl = dynamic_cast<ProjectLeader *>(entry.second);
        if (pl)
        {
            cout << "Payroll Number: " << pl->getPayrollNumber() << endl;
            cout << "Name          : " << pl->getName() << endl;
            cout << "Monthly Salary: " << pl->getMonthlySalary() << endl;
            cout << "Programming Language: " << pl->getLanguage() << endl;
            cout << "--------------------------------------------------" << endl;
        }
    }
}

void SoftwareHouse::display()
{
    cout << "Software House: " << this->getClassName() << endl;
    cout << "\tStaff:" << endl;
    this->displayStaff();
    cout << "\tProject Leaders:" << endl;
    this->displayProjectLeaders();
    cout << "--------------------------------------------------" << endl;
}
/*----------------------------------------------------------------*/
// The main function demonstrates the functionality of the classes.
// It creates a SoftwareHouse object, adds Programmer objects to it,
// displays their details, and cleans up the allocated memory.

int main()
{
    Programmer a("001", "John", 1000, "C++");
    Programmer b("002", "Jane", 2000, "Java");
    ProjectLeader c("004", "Jack", 4000, "Python");

    c.addProgrammer(&a);
    c.addProgrammer(&b);

    SoftwareHouse d("Facebook");
    d.addStaff(&a);
    d.addStaff(&b);
    d.addStaff(&c);
    d.display();

    return 0;
}


// Revison 2:
#include <iostream>
#include <map>
#include <list>
#include <string>
using namespace std;

class Hospital;
class Department;

class Person;
class Patient;
class Doctor;

class DoctorGroup;
class LeaderDoctor;

/*--------------------------------------------------*/
class Person{
    string name;
public:
    // Constructor
    Person(string name);
    // Setter
    void setname(string name);
    // Getter
    string getname();
};
/*--------------------------------------------------*/
class Hospital{
    string name;
    map<string, Department*> departments;
public:
    // Constructor
    Hospital(string name);
    // Setter
    void setname(string name);
    void addDepartment(Department *department);
    // Getter
    string getname();
    map<string, Department*> getDepartments();
    // Methods
    void attachDepartment(Department *department);
    void detachDepartment(Department *department);
    // Display
    void display_Hospital();
};
/*--------------------------------------------------*/
class Department{
    string name;
    map<string, Patient*> patients;
public:
    // Constructor
    Department(string name);
    // Setter
    void setname(string name);
    void addPatients(Patient *patient);
    // Getter
    string getname();
    list<Patient *> getPatients();
    // Methods
    void attachPatient(Patient *patient);
    void detachPatient(Patient *patient);
    void detachAll_A();
    // Display
    void display_Department();
};
/*--------------------------------------------------*/
class Patient : public Person
{
    string date;
    Department *department;
    DoctorGroup *doctorGroup;
public:
    // Constructor
    Patient(string name, string date);
    // Setter
    void setdate(string date);
    void setDepartment(Department *department);
    void setDoctorGroup(DoctorGroup *doctorGroup);
    // Getter
    string getdate();
    Department *getDepartment();
    DoctorGroup *getDoctorGroup();
    // Methods
    void attachDepartment(Department *department);
    void detachDepartment(Department *department);
    void detachAll_A();
    // Display
    void display_Patient();
};
/*--------------------------------------------------*/
class DoctorGroup{
    string name;
    string GroupID;
    list<Doctor *> doctors;
public:
    // Constructor
    DoctorGroup(string name);
    // Setter
    void setname(string name);
    void addDoctors(Doctor *doctor);
    void setGroupID(string GroupID);
    // Getter
    string getname();
    string getGroupID();
    list<Doctor *> getDoctors();
    // Methods
    void attachDoctor(Doctor *doctor);
    void detachDoctor(Doctor *doctor);
    void detachAll_A();
    // Display
    void display_DoctorGroup();
};
/*--------------------------------------------------*/
class Doctor: public Person{
    string address;
    list<Patient *> patients;
    DoctorGroup *doctorGroup;
public:
    // Constructor
    Doctor(string name, string address);
    // Setter
    void setaddress(string address);
    void setDoctorGroup(DoctorGroup *doctorGroup);
    void addPatients(Patient *patient);
    // Getter
    string getaddress();
    DoctorGroup *getDoctorGroup();
    list<Patient *> getPatients();
    // Methods
    void attachPatient(Patient *patient);
    void detachPatient(Patient *patient);
    void detachAll_A();
    // Display
    void display_Doctor();
};
/*--------------------------------------------------*/
class LeaderDoctor: public Doctor{
    list<Doctor *> doctors;
public:
    // Constructor
    LeaderDoctor(string name, string address);
    // Setter
    void addDoctors(Doctor *doctor);
    // Getter
    list<Doctor *> getDoctors();
    // Methods
    void attachDoctor(Doctor *doctor);
    void detachDoctor(Doctor *doctor);
    void detachAll_A();
    // Display
    void display_LeaderDoctor();
};

/*---------------------CLASS PERSON-----------------------------*/
Person::Person(string name)
{
    this->setname(name);
}
void Person::setname(string name)
{
    this->name = name;
}
string Person::getname()
{
    return this->name;
}
/*---------------------CLASS HOSPITAL-----------------------------*/
// Constructor
Hospital::Hospital(string name)
{
    this->setname(name);
}
// Setter
void Hospital::setname(string name)
{
    this->name = name;
}
void Hospital::addDepartment(Department *department)
{
    this->departments[department->getname()] = department;
}
// Getter
string Hospital::getname()
{
    return this->name;
}
map<string, Department*> Hospital::getDepartments()
{
    return this->departments;
}
// Methods
void Hospital::attachDepartment(Department *department)
{
    this->addDepartment(department);
}
void Hospital::detachDepartment(Department *department)
{
    this->departments.erase(department->getname());
}
// Display
void Hospital::display_Hospital()
{
    cout << "The Name: " << this->getname() << endl;
    cout << "--------------------------" << endl;
    cout << "Departments: " << endl;
    for (auto department : this->departments)
    {
        department.second->display_Department();
    }
}
/*---------------------CLASS DEPARTMENT-----------------------------*/
// Constructor
Department::Department(string name)
{
    this->setname(name);
}
// Setter
void Department::setname(string name)
{
    this->name = name;
}
void Department::addPatients(Patient *patient)
{
    this->patients[patient->getname()] = patient;
}
// Getter
string Department::getname()
{
    return this->name;
}
list<Patient *> Department::getPatients()
{
    list<Patient *> patientList;
    for (auto patient : this->patients)
    {
        patientList.push_back(patient.second);
    }
    return patientList;
}
// Methods
void Department::attachPatient(Patient *patient)
{
    this->addPatients(patient);
    patient->setDepartment(this);
}
void Department::detachPatient(Patient *patient)
{
    this->patients.erase(patient->getname());
}
void Department::detachAll_A()
{
    for (auto patient : this->getPatients())
    {
        patient->setDepartment(nullptr);
    }
}
// Display
void Department::display_Department()
{
    cout << "o--------------------------o" << endl;
    cout << "The Name: " << this->getname() << endl;
    cout << "Patients: " << endl;
    for (auto patient : this->getPatients())
    {
        cout << "Patient Name: " << patient->getname() << endl;
    }
}
/*---------------------CLASS PATIENT-----------------------------*/
// Constructor
Patient::Patient(string name, string date): Person(name)
{
    this->setdate(date);
}
// Setter
void Patient::setdate(string date)
{
    this->date = date;
}
void Patient::setDepartment(Department *department)
{
    this->department = department;
}
void Patient::setDoctorGroup(DoctorGroup *doctorGroup)
{
    this->doctorGroup = doctorGroup;
}
// Getter
string Patient::getdate()
{
    return this->date;
}
Department *Patient::getDepartment()
{
    return this->department;
}
DoctorGroup *Patient::getDoctorGroup()
{
    return this->doctorGroup;
}
// Methods
void Patient::attachDepartment(Department *department)
{
    this->setDepartment(department);
    department->attachPatient(this);
}
void Patient::detachDepartment(Department *department)
{
    this->department = nullptr;
}
void Patient::detachAll_A()
{
    this->setDepartment(nullptr);
}
// Display
void Patient::display_Patient()
{
    cout << "The Name: " << this->getname() << endl;
    cout << "The Date: " << this->getdate() << endl;
    cout << "Department: " << this->getDepartment()->getname() << endl;
    cout << "Doctor Group: " << (this->getDoctorGroup() ? this->getDoctorGroup()->getname() : "None") << endl;
    cout << "#--------------------------#" << endl;
}

/*---------------------CLASS DOCTOR GROUP-----------------------------*/
// Constructor
DoctorGroup::DoctorGroup(string name)
{
    this->setname(name);
}
// Setter
void DoctorGroup::setname(string name)
{
    this->name = name;
}
void DoctorGroup::addDoctors(Doctor *doctor)
{
    this->doctors.push_back(doctor);
}
void DoctorGroup::setGroupID(string GroupID)
{
    this->GroupID = GroupID;
}
// Getter
string DoctorGroup::getname()
{
    return this->name;
}
string DoctorGroup::getGroupID()
{
    return this->GroupID;
}
list<Doctor *> DoctorGroup::getDoctors()
{
    return this->doctors;
}
// Methods
void DoctorGroup::attachDoctor(Doctor *doctor)
{
    this->addDoctors(doctor);
    doctor->setDoctorGroup(this);
}
void DoctorGroup::detachDoctor(Doctor *doctor)
{
    this->doctors.remove(doctor);
}
void DoctorGroup::detachAll_A()
{
    for (auto doctor : this->getDoctors())
    {
        doctor->setDoctorGroup(nullptr);
    }
}
// Display
void DoctorGroup::display_DoctorGroup()
{
    cout << "The Name: " << this->getname() << endl;
    cout << "Doctors: " << endl;
    for (auto doctor : this->getDoctors())
    {
        cout << "Doctor Name: " << doctor->getname() << endl;
    }
}
/*---------------------CLASS DOCTOR-----------------------------*/
// Constructor
Doctor::Doctor(string name, string address): Person(name)
{
    this->setaddress(address);
}   
// Setter
void Doctor::setaddress(string address)
{
    this->address = address;
}
void Doctor::setDoctorGroup(DoctorGroup *doctorGroup)
{
    this->doctorGroup = doctorGroup;
}
void Doctor::addPatients(Patient *patient)
{
    this->patients.push_back(patient);
}
// Getter
string Doctor::getaddress()
{
    return this->address;
}
DoctorGroup *Doctor::getDoctorGroup()
{
    return this->doctorGroup;
}
list<Patient *> Doctor::getPatients()
{
    return this->patients;
}
// Methods
void Doctor::attachPatient(Patient *patient)
{
    this->addPatients(patient);
    patient->setDoctorGroup(this->doctorGroup);
    patient->setDepartment(nullptr);
}
void Doctor::detachPatient(Patient *patient)
{
    this->patients.remove(patient);
}
void Doctor::detachAll_A()
{
    for (auto patient : this->getPatients())
    {
        patient->setDoctorGroup(nullptr);
    }
}
// Display
void Doctor::display_Doctor()
{
    cout << "The Name: " << this->getname() << endl;
    cout << "The Address: " << this->getaddress() << endl;
    cout << "Patients: " << endl;
    for (auto patient : this->getPatients())
    {
        cout << "Patient Name: " << patient->getname() << endl;
    }
}
/*---------------------CLASS LEADER DOCTOR-----------------------------*/
// Constructor
LeaderDoctor::LeaderDoctor(string name, string address): Doctor(name, address)
{
}
// Setter
void LeaderDoctor::addDoctors(Doctor *doctor)
{
    this->doctors.push_back(doctor);
}
// Getter
list<Doctor *> LeaderDoctor::getDoctors()
{
    return this->doctors;
}
// Methods
void LeaderDoctor::attachDoctor(Doctor *doctor)
{
    this->addDoctors(doctor);
    doctor->setDoctorGroup(this->getDoctorGroup());
}
void LeaderDoctor::detachDoctor(Doctor *doctor)
{
    this->doctors.remove(doctor);  
    doctor->setDoctorGroup(nullptr);
}
void LeaderDoctor::detachAll_A()
{
    for (auto doctor : this->getDoctors())
    {
        doctor->setDoctorGroup(nullptr);
    }
}
// Display
void LeaderDoctor::display_LeaderDoctor()
{
    cout << "The Name: " << this->getname() << endl;
    cout << "Doctors: " << endl;
    for (auto doctor : this->getDoctors())
    {
        cout << "Doctor Name: " << doctor->getname() << endl;
    }
}
/*---------------------MAIN FUNCTION-----------------------------*/
int main()
{
    Hospital h("City Hospital");
    
    // Create departments
    Department *Cardiology = new Department("Cardiology");
    Department *Neurology = new Department("Neurology");

    // Create patients
    Patient *p1 = new Patient("Minh Duy", "2023-10-01");
    Patient *p2 = new Patient("Nguyen Hoang", "2023-23-02");
    Patient *p3 = new Patient("Le Quoc Thinh", "2025-06-05");
    Patient *p4 = new Patient("Nguyen Minh", "2024-10-11");
    Patient *p5 = new Patient("Nguyen Hieu", "2023-12-12");

    // Create doctors
    Doctor *d1 = new Doctor("Dr. Nguyen", "123 Main St");
    Doctor *d2 = new Doctor("Dr. Tran", "456 Elm St");
    Doctor *d3 = new Doctor("Dr. Le", "789 Oak St");
    Doctor *d4 = new Doctor("Dr. Pham", "101 Pine St");
    Doctor *d5 = new Doctor("Dr. Ho", "202 Maple St");

    // Create doctor group
    DoctorGroup *CardiologyGroup = new DoctorGroup("Cardiology Group");
    CardiologyGroup->setGroupID("CG001");
    CardiologyGroup->attachDoctor(d1);
    CardiologyGroup->attachDoctor(d2);

    DoctorGroup *NeurologyGroup = new DoctorGroup("Neurology Group");
    NeurologyGroup->setGroupID("NG001");
    NeurologyGroup->attachDoctor(d3);
    NeurologyGroup->attachDoctor(d4);
    NeurologyGroup->attachDoctor(d5);

    // Create leader doctor
    LeaderDoctor *leader = new LeaderDoctor("Dr. Le", "789 Oak St");
    leader->setDoctorGroup(CardiologyGroup);
    leader->attachDoctor(d1);
    leader->attachDoctor(d2);
    
    LeaderDoctor *leader2 = new LeaderDoctor("Dr. Pham", "101 Pine St");
    leader2->setDoctorGroup(NeurologyGroup);
    leader2->attachDoctor(d3);
    leader2->attachDoctor(d4);
    leader2->attachDoctor(d5);
        
    // Attach patients to departments
    Cardiology->attachPatient(p1);
    Cardiology->attachPatient(p3);
    Cardiology->attachPatient(p4);
    
    Neurology->attachPatient(p2);
    Neurology->attachPatient(p5);
    
    p1->attachDepartment(Cardiology);
    p2->attachDepartment(Neurology);

    // Set doctor groups for patients
    p1->setDoctorGroup(CardiologyGroup);
    p2->setDoctorGroup(NeurologyGroup);
    p3->setDoctorGroup(CardiologyGroup);
    p4->setDoctorGroup(CardiologyGroup);
    p5->setDoctorGroup(NeurologyGroup);
    
    // Attach doctors to doctor groups
    CardiologyGroup->attachDoctor(d1);
    CardiologyGroup->attachDoctor(d2);
    NeurologyGroup->attachDoctor(d3);
    NeurologyGroup->attachDoctor(d4);
    NeurologyGroup->attachDoctor(d5);
    
    // Attach departments to hospital
    h.attachDepartment(Cardiology);
    h.attachDepartment(Neurology);
    
    // Display Information
    // Display hospital information
    h.display_Hospital();
    cout << "-------------------------" << endl;

    // Display Doctor Group information
    cout << "Display Doctor Group Information" << endl;
    cout << "-------------------------" << endl;
    cout << "Doctor Group: " << CardiologyGroup->getname() << endl;
    CardiologyGroup->display_DoctorGroup();
    cout << "Doctor Group: " << NeurologyGroup->getname() << endl;
    NeurologyGroup->display_DoctorGroup();
    cout << "-------------------------" << endl;

    // Display Leader Doctor information
    cout << "Display Leader Doctor Information" << endl;
    cout << "-------------------------" << endl;
    cout << "Leader Doctor: " << leader->getname() << endl;
    leader->display_LeaderDoctor();
    cout << "Leader Doctor: " << leader2->getname() << endl;
    leader2->display_LeaderDoctor();
    cout << "-------------------------" << endl;

    // Display department information
    cout << "Display Department Information" << endl;
    cout << "-------------------------" << endl;
    cout << "Department: " << Cardiology->getname() << endl;
    Cardiology->display_Department();
    cout << "Department: " << Neurology->getname() << endl;
    Neurology->display_Department();
    cout << "-------------------------" << endl;
    
    // Display patient information
    cout << "Display Patient Information" << endl;
    cout << "-------------------------" << endl;
    cout << "Patient 1: " << endl;
    p1->display_Patient();
    cout << "Patient 2: " << endl;
    p2->display_Patient();
    cout << "Patient 3: " << endl;
    p3->display_Patient();
    cout << "Patient 4: " << endl;
    p4->display_Patient();
    cout << "Patient 5: " << endl;
    p5->display_Patient();

    // Clean up
    // Delete patients
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    // Delete doctors
    delete d1;
    delete d2;
    delete d3;
    delete d4;
    delete d5;
    // Delete doctor groups
    delete CardiologyGroup;
    delete NeurologyGroup;
    // Delete leader doctors
    delete leader2;
    delete leader;
    // Delete departments
    delete Cardiology;
    delete Neurology;

    return 0;
}

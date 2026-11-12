#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <memory>

using namespace std;

class Person {
protected:
    string name;
    int id;

public:
    Person() : name("Undefined"), id(0) {}
    Person(const string& n, int i) : name(n), id(i) {}
    Person(const Person& other) : name(other.name), id(other.id) {}

    virtual ~Person() {}

    void setName(const string& n) { name = n; }
    string getName() const { return name; }
    void setId(int i) { id = i; }
    int getId() const { return id; }

    virtual void readData() {
        cout << "Enter name: ";
        getline(cin >> ws, name);
        cout << "Enter ID: ";
        cin >> id;
    }

    virtual void printData() const {
        cout << "[Person] ID: " << id << " | Name: " << name << endl;
    }
};

class Employee : public Person {
private:
    string position;
    double assignedBudget;
    string assignedResource;

public:
    Employee()
        : Person(), position("Worker"), assignedBudget(0.0), assignedResource("None") {
    }

    Employee(const string& n, int i, const string& pos, double budget, const string& resource)
        : Person(n, i), position(pos), assignedBudget(budget), assignedResource(resource) {
    }

    Employee(const Employee& other)
        : Person(other), position(other.position), assignedBudget(other.assignedBudget), assignedResource(other.assignedResource) {
    }

    ~Employee() override {}

    void setPosition(const string& pos) { position = pos; }
    void setAssignedBudget(double budget) { assignedBudget = budget; }
    void setAssignedResource(const string& res) { assignedResource = res; }
    double getAssignedBudget() const { return assignedBudget; }
    string getPosition() const { return position; }

    void readData() override {
        Person::readData();
        cout << "Enter position: ";
        getline(cin >> ws, position);
        cout << "Enter assigned budget: ";
        cin >> assignedBudget;
        cout << "Enter assigned resource (e.g., Software/Hardware): ";
        getline(cin >> ws, assignedResource);
    }

    void printData() const override {
        cout << "[Employee] ID: " << id << " | Name: " << name
            << " | Position: " << position
            << " | Budget: " << assignedBudget << " $"
            << " | Resource: " << assignedResource << endl;
    }
};

class Manager : public Person {
private:
    string projectAssigned;
    double managedBudget;
    int managedTeamsCount;

public:
    Manager()
        : Person(), projectAssigned("None"), managedBudget(0.0), managedTeamsCount(0) {
    }

    Manager(const string& n, int i, const string& proj, double budget, int teams)
        : Person(n, i), projectAssigned(proj), managedBudget(budget), managedTeamsCount(teams) {
    }

    Manager(const Manager& other)
        : Person(other), projectAssigned(other.projectAssigned), managedBudget(other.managedBudget), managedTeamsCount(other.managedTeamsCount) {
    }

    ~Manager() override {}

    void setProject(const string& proj) { projectAssigned = proj; }
    void allocateBudget(double amount) { managedBudget += amount; }
    void setTeamsCount(int count) { managedTeamsCount = count; }
    double getManagedBudget() const { return managedBudget; }
    int getTeamsCount() const { return managedTeamsCount; }

    void readData() override {
        Person::readData();
        cout << "Enter assigned project name: ";
        getline(cin >> ws, projectAssigned);
        cout << "Enter managed budget: ";
        cin >> managedBudget;
        cout << "Enter number of teams under management: ";
        cin >> managedTeamsCount;
    }

    void printData() const override {
        cout << "[Manager] ID: " << id << " | Manager: " << name
            << " | Project: " << projectAssigned
            << " | Managed Budget: " << managedBudget << " $"
            << " | Teams under management: " << managedTeamsCount << endl;
    }
};

class Project {
private:
    string projectName;
    string customerName;
    double totalBudget;
    string status;
    int teamCount;

public:
    Project()
        : projectName("Untitled"), customerName("Unknown"), totalBudget(0.0), status("Planning"), teamCount(1) {
    }

    Project(const string& pName, const string& cName, double budget, const string& st, int teams)
        : projectName(pName), customerName(cName), totalBudget(budget), status(st), teamCount(teams) {
    }

    Project(const Project& other)
        : projectName(other.projectName), customerName(other.customerName),
        totalBudget(other.totalBudget), status(other.status), teamCount(other.teamCount) {
    }

    ~Project() {}

    void setBudget(double b) { totalBudget = b; }
    void setStatus(const string& st) { status = st; }
    void addTeam() { teamCount++; }
    string getProjectName() const { return projectName; }
    double getTotalBudget() const { return totalBudget; }

    void readData() {
        cout << "Enter project name: ";
        getline(cin >> ws, projectName);
        cout << "Enter customer name: ";
        getline(cin >> ws, customerName);
        cout << "Enter total project budget: ";
        cin >> totalBudget;
        cout << "Enter project status (In Progress/Completed/Planning): ";
        getline(cin >> ws, status);
        cout << "Enter number of teams involved: ";
        cin >> teamCount;
    }

    void printData() const {
        cout << "[Project] Project: " << projectName
            << " | Customer: " << customerName
            << " | Budget: " << totalBudget << " $"
            << " | Status: " << status
            << " | Number of teams: " << teamCount << endl;
    }
};

int main() {
    vector<unique_ptr<Person>> persons;
    persons.push_back(make_unique<Person>("Oleksii Petrov", 101));
    persons.push_back(make_unique<Employee>("Ivan Kovalenko", 102, "C++ Developer", 5000.0, "Workstation PC & Visual Studio"));
    persons.push_back(make_unique<Manager>("Maria Sydorenko", 103, "ERP System Redesign", 50000.0, 3));

    vector<Project> projects;
    projects.emplace_back("ERP System Redesign", "TechCorp Global", 50000.0, "In Progress", 3);

    cout << "=== Persons Collection ===" << endl;
    for (const auto& p : persons) {
        p->printData();
    }

    cout << "\n=== Projects Collection ===" << endl;
    for (const auto& proj : projects) {
        proj.printData();
    }

    return 0;
}
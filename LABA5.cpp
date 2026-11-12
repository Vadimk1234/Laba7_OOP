#include "ProjectManagement.h"
#include <iostream>
#include <vector>
#include <memory>

Budget::Budget(double limit) : totalLimit(limit), spentAmount(0.0) {}

double Budget::getLimit() const { return totalLimit; }
double Budget::getSpentAmount() const { return spentAmount; }

bool Budget::allocateFunds(double amount) {
    if (spentAmount + amount <= totalLimit) {
        spentAmount += amount;
        return true;
    }
    return false;
}

void Budget::reset() { spentAmount = 0.0; }

Employee::Employee(const std::string& empName, double initialBudget)
    : name(empName), budget(initialBudget) {
}

void Employee::reportStatus() const {
    std::cout << "Participant: " << name
        << " | Budget spent: " << budget.getSpentAmount()
        << " of " << budget.getLimit() << std::endl;
}

std::string Employee::getName() const { return name; }
Budget& Employee::getBudget() { return budget; }

OfficeWorker::OfficeWorker(const std::string& empName, double initialBudget, const std::string& spec)
    : Employee(empName, initialBudget), specialty(spec) {
}

void OfficeWorker::performWork() {
    std::cout << "Office worker " << name << " (" << specialty
        << ") is performing an individual task.\n";
    budget.allocateFunds(150.0);
}

void OfficeWorker::reportStatus() const {
    std::cout << "[Office Worker] ";
    Employee::reportStatus();
}

Team::Team(const std::string& teamName, double initialBudget)
    : Employee(teamName, initialBudget) {
}

void Team::addMember(Employee* member) {
    members.push_back(member);
}

void Team::performWork() {
    std::cout << "Team \"" << name << "\" has started the group part of the project.\n";
    for (auto* member : members) {
        member->performWork();
    }
}

void Team::reportStatus() const {
    std::cout << "[Team] " << name << " consists of " << members.size() << " members.\n";
    Employee::reportStatus();
}

ProjectManager::ProjectManager(const std::string& managerName, double totalBudget)
    : Employee(managerName, totalBudget) {
}

void ProjectManager::assignTask(Employee* worker, double taskBudget) {
    std::cout << "Manager " << name << " assigned a task to " << worker->getName()
        << " with a budget of: " << taskBudget << "\n";
    budget.allocateFunds(taskBudget);
}

void ProjectManager::performWork() {
    std::cout << "Manager " << name << " oversees the project and manages the budget.\n";
}

void ProjectManager::reportStatus() const {
    std::cout << "[Project Manager] ";
    Employee::reportStatus();
}

int main() {
    std::vector<std::unique_ptr<Employee>> employees;

    employees.push_back(std::make_unique<OfficeWorker>("Ivan", 1000.0, "Developer"));
    employees.push_back(std::make_unique<OfficeWorker>("Olena", 1000.0, "Designer"));
    employees.push_back(std::make_unique<ProjectManager>("Maria", 10000.0));

    auto team = std::make_unique<Team>("Alpha Team", 5000.0);
    team->addMember(employees[0].get());
    team->addMember(employees[1].get());
    employees.push_back(std::move(team));

    for (const auto& emp : employees) {
        emp->reportStatus();
        emp->performWork();
        std::cout << "----------------------------------------\n";
    }

    return 0;
}
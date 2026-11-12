#include <iostream>
#include <string>
#include <iomanip>
#include <cinttypes>
#include <locale>
#include <vector>

class ProjectManagement {
private:
	std::string projectName;
	std::string managerName;
	double budget;
	int workersCount;
	std::string resources;

public:
	ProjectManagement(std::string pName = "Undefined",
		std::string mName = "Unknown",
		double b = 0.0,
		int w = 0,
		std::string res = "None")
		: projectName(pName), managerName(mName), budget(b), workersCount(w), resources(res) {
		std::cout << "[Builder] Project created: " << projectName << std::endl;
	}

	~ProjectManagement() {
		std::cout << "[Builder] Project deleted: " << projectName << std::endl;
	}

	void setProjectName(const std::string& pName) { projectName = pName; }
	void setManagerName(const std::string& mName) { managerName = mName; }
	void setBudget(double b) { budget = b; }
	void setWorkersCount(int w) { workersCount = w; }
	void setResources(const std::string& res) { resources = res; }

	std::string getProjectName() const { return projectName; }
	std::string getManagerName() const { return managerName; }
	double getBudget() const { return budget; }
	int getWorkersCount() const { return workersCount; }
	std::string getResources() const { return resources; }

	void printInfo() const {
		std::cout << "Project: " << projectName << std::endl;
		std::cout << "Manager: " << managerName << std::endl;
		std::cout << "Budget: $" << std::fixed << std::setprecision(2) << budget << std::endl;
		std::cout << "Number of workers: " << workersCount << std::endl;
		std::cout << "Resources: " << resources << std::endl;
	}

	friend void updateBudget(ProjectManagement& project, double amount);
};

void updateBudget(ProjectManagement& project, double amount) {
	project.budget += amount;
	std::cout << "[Friendly function] Project budget '" << project.projectName
		<< "' changed by $" << amount << ". New budget: $"
		<< std::fixed << std::setprecision(2) << project.budget << std::endl;
}

int main() {
	std::locale::global(std::locale(""));

	std::vector<ProjectManagement> projects;

	projects.emplace_back("E-Commerce Platform", "Vadim", 15000.0, 5, "Servers, Figma, IDE");
	projects.emplace_back("Mobile Banking App", "Olena", 28000.0, 8, "React Native, AWS, Docker");
	projects.emplace_back("AI Analytics Tool", "Max", 45000.0, 12, "Python, TensorFlow, Kubernetes");

	std::cout << "\n----------------------------------------\n";
	std::cout << "Вивід усіх проєктів з контейнера vector:" << std::endl;
	std::cout << "----------------------------------------\n";

	for (const auto& proj : projects) {
		proj.printInfo();
		std::cout << "----------------------------------------" << std::endl;
	}

	std::cout << "\nОновлення даних першого проєкту через векторизований доступ..." << std::endl;
	projects[0].setWorkersCount(8);
	projects[0].setResources("Servers, Figma, IDE, CI/CD Pipeline");

	updateBudget(projects[0], 3500.0);

	std::cout << "\n----------------------------------------\n";
	std::cout << "Підсумковий стан оновленого проєкту:" << std::endl;
	std::cout << "----------------------------------------\n";
	projects[0].printInfo();

	return 0;
}
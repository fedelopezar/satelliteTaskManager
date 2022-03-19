#include "taskManager.hpp"
#include "classTask.hpp"

/* Default constructor */
Task::Task()
{
    taskId = "undefined";
    name = "undefined";
    resources = std::vector<int>();
    payoff = 0. / 0.;
    assignedToSatelliteId = "undefined";
    completed = false;
    timeStart = "undefined";
    timeEnd = "undefined";
};

/* Destructor */
Task::~Task()
{
    this->resources = std::vector<int>(); // Release vector memory
};

/* Set Task details from JSON object */
void Task::setFromJSONObj(std::string x, json y)
{
    taskId = x;
    name = y["name"];
    for (auto resource : y["resources"])
    { // Moving resources from JSON to resources attribute
        resources.push_back(resource);
    }
    payoff = y["payoff"];
    completed = y["completed"];
};

/* Print Task details */
void Task::print()
{
    std::cout << "===" << std::endl;
    std::cout << "taskID: " << this->taskId << std::endl;
    std::cout << "name: " << this->name << std::endl;
    std::cout << "payoff: " << this->payoff << std::endl;
    std::cout << "resources: [ ";
    for (auto resource : this->resources)
    {
        std::cout << resource << " ";
    }
    std::cout << "]" << std::endl
              << "===" << std::endl;
};

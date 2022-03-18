#include "taskManager.hpp"
#include "classTask.hpp"

/* Default constructor */
Task::Task()
{
    taskId = "undefined";
    name = "undefined";
    payoff = 0. / 0.;
    assignedToSatelliteId = "undefined";
    completed = false;
    timeStart = "undefined";
    timeEnd = "undefined";
};

/* Destructor */
Task::~Task()
{
    this->resources = std::vector<int>();
};

/* Set task from JSON object */
void Task::setFromJSONObj(std::string x, json y)
{
    taskId = x;
    name = y["name"];
    int resourcesNumber = y["resources"].size(); // Get the number of resources
    for (int counter = 0; counter < resourcesNumber; ++counter)
    {
        resources.push_back(y["resources"][counter]);
    };
    payoff = y["payoff"];
    completed = y["completed"];
};

/* Print task details */
void Task::print()
{
    std::cout << "===" << std::endl;
    std::cout << "taskID: " << this->taskId << std::endl;
    std::cout << "name: " << this->name << std::endl;
    std::cout << "payoff: " << this->payoff << std::endl;
    std::cout << "===" << std::endl;
};

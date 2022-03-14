#include "taskManager.hpp"
#include "classTask.hpp"

/* Default constructor */
Task::Task()
{
    taskId = "undefined";
    name = "undefined";
    resources = NULL;
    payoff = 0. / 0.;
};

/* Destructor */
Task::~Task()
{
    delete[] resources;
};

/* Set task from JSON object      */
// TODO: redefine as constructor?
void Task::setFromJSONObj(std::string x, json y)
{
    taskId = x;
    name = y["name"];
    int resourcesNumber = y["resources"].size(); // Get the number of resources
    resources = new int[resourcesNumber];        // Allocate array of resources
    for (int counter = 0; counter < resourcesNumber; ++counter)
    {
        resources[counter] = y["resources"][counter];
    };
    payoff = y["payoff"];
};

/* Print task details */
void Task::print()
{
    std::cout << "===" << std::endl;
    std::cout << "taskID: " << this->taskId << std::endl;
    std::cout << "name: " << this->name << std::endl;
    std::cout << "resources: " << this->resources << std::endl;
    std::cout << "payoff: " << this->payoff << std::endl;
    std::cout << "===" << std::endl;
};
#include "taskManager.hpp"
#include "classTask.hpp"
#include "classSatellite.hpp"

Task *getTasks(char *tasksInput, int &tasksNumber)
{
    std::ifstream tasksInputFile(tasksInput); // Read tasks from file
    json tasksJSON;                           // Tasks to JSON object
    tasksInputFile >> tasksJSON;              //
    tasksNumber = tasksJSON.size();           // Total number of tasks
    Task *tasksArray = new Task[tasksNumber]; // Create array of Task objects (calling default constructor)
    int counter = 0;
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        tasksArray[counter].setFromJSONObj(taskJSONObj.key(), taskJSONObj.value()); // Set each Task details
        ++counter;
    }
    return tasksArray;
};

Satellite *getSatellites(char *satellitesInput, int &satellitesNumber)
{
    std::ifstream tasksInputFile(satellitesInput); // Read satellites from file
    json tasksJSON;                                // Satellites to JSON object
    tasksInputFile >> tasksJSON;                   //
    satellitesNumber = tasksJSON.size();           // Total number of tasks
    Satellite *satellitesArray = new Satellite[satellitesNumber];      // Create array of Satellite objects (calling default constructor)
    int counter = 0;
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        satellitesArray[counter].setFromJSONObj(taskJSONObj.key(), taskJSONObj.value()); // Set each Task details
        ++counter;
    }
    return satellitesArray;
}

int getIndexInt(int *array, int length, int value)
{
    int i = 0;
    while (i < length && array[i] != value)
    {
        ++i;
    }
    return (i < length) ? i : 0 / 0;
}

bool checkResources(std::vector<int> resourcesInUse, std::vector<int> resourcesToUse)
{
    for (int i : resourcesToUse)
    {
        for (int j : resourcesInUse)
        {
            if (i == j)
                return false;
        }
    }
    return true;
}
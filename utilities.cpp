#include "taskManager.hpp"
#include "classTask.hpp"
#include "classSatellite.hpp"

void getTasks(char *tasksInput, std::vector<Task> &tasksVec)
{
    std::ifstream tasksInputFile(tasksInput); // Read tasks from file
    json tasksJSON;                           // Tasks to JSON object
    tasksInputFile >> tasksJSON;              //
    int tasksNumber = tasksJSON.size();       // Total number of tasks
    int counter = 0;
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        tasksVec.push_back(Task());                                               // Initialize default task
        tasksVec[counter].setFromJSONObj(taskJSONObj.key(), taskJSONObj.value()); // Set each Task details
        ++counter;
    }
    for (counter = 0; counter < tasksNumber; ++counter) // Ignore completed tasks
    {
        if (tasksVec[counter].completed)
        {
            std::cout << "Ignoring " << tasksVec[counter].taskId << " since has been completed." << std::endl;
            tasksVec.erase(tasksVec.begin() + counter);
            --tasksNumber;
            --counter;
        }
    }
};

void getSatellites(char *satellitesInput, std::vector<Satellite> &satellitesVec)
{
    std::ifstream tasksInputFile(satellitesInput); // Read satellites from file
    json tasksJSON;                                // Satellites to JSON object
    tasksInputFile >> tasksJSON;                   //
    int satellitesNumber = tasksJSON.size();       // Total number of tasks
    int counter = 0;
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        satellitesVec.push_back(Satellite());
        satellitesVec[counter].setFromJSONObj(taskJSONObj.key(), taskJSONObj.value()); // Set each Task details
        ++counter;
    }
}

void sortTasksByPayoff(std::vector<Task> &tasksVec)
{
    int n = tasksVec.size();
    int new_n;
    int counter;

    while (n > 0)
    {
        new_n = 0;
        for (counter = 0; counter < (n - 1); ++counter)
        {
            if (tasksVec[counter].payoff < tasksVec[counter + 1].payoff)
            {
                std::swap(tasksVec[counter], tasksVec[counter + 1]);
                new_n = counter+1;
            }
        }
        n = new_n;
    }
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

void assignSatellitesToTasks(std::vector<Task> &tasksVec, std::vector<Satellite> &satellitesVec)
{
    int tasksNumber = tasksVec.size();
    int satellitesNumber = satellitesVec.size();
    int itTask, itSatellite;

    for (int itTask = 0; itTask < tasksNumber; ++itTask)
    {
        std::cout << "-- " << tasksVec[itTask].taskId << " received" << std::endl;
        for (int itSatellite = 0; itSatellite < satellitesNumber; ++itSatellite)
        {
            if (checkResources(satellitesVec[itSatellite].resourcesInUse, tasksVec[itTask].resources)) // Check if this satellite have resources available
            {
                for (auto i : tasksVec[itTask].resources)
                {
                    satellitesVec[itSatellite].resourcesInUse.push_back(i); // Update resources in use
                }
                tasksVec[itTask].assignedToSatelliteId = satellitesVec[itSatellite].satelliteId;
                std::cout << tasksVec[itTask].taskId << " assigned to " << satellitesVec[itSatellite].satelliteId << std::endl;
                break;
            }
            else
            {
                std::cout << "Can't assign " << tasksVec[itTask].taskId << " to " << satellitesVec[itSatellite].satelliteId << ", resources occupied " << std::endl;
            }
        }
    }
}

#include "taskManager.hpp"
#include "classTask.hpp"
#include "classSatellite.hpp"
#include "utilities.hpp"

int main(int argc, char **argv)
{
    int counter, counterNested;

    /* Create array of Task objects from input */
    int tasksNumber;                                   // Total number of tasks
    Task *tasksArray = getTasks(argv[1], tasksNumber); // TODO: Move tasksArray to vec?

    /* =============================== */
    /* Create array of task priorities */
    // TODO: Move to function
    /* =============================== */
    int *priorityTasksArray; // Array of priorities for each task, being 0 the highest and tasksNumber the lowest
    priorityTasksArray = new int[tasksNumber];
    int tmpPriority;
    for (counter = 0; counter < tasksNumber; ++counter)
    {
        tmpPriority = 0;
        for (counterNested = 0; counterNested < tasksNumber; ++counterNested)
        {
            if (tasksArray[counter].payoff < tasksArray[counterNested].payoff)
            {
                tmpPriority += 1;
            }
        }
        priorityTasksArray[counter] = tmpPriority;
    }
    for (counter = 0; counter < tasksNumber; ++counter) // If tasks have same payoff, prioritize by order
    {
        if (priorityTasksArray[counter] == priorityTasksArray[counter + 1])
        {
            priorityTasksArray[counter + 1] += 1;
        }
    }

    /* ================================= */
    /* Create array of Satellite objects */
    // TODO: Move to function
    /* ================================= */
    // std::ifstream satellitesInputFile(argv[2]);
    // json satellitesJSON;
    // satellitesInputFile >> satellitesJSON;
    // int satellitesNumber = 0; // Get number of satellites
    // for (json::iterator satellitesJSONObj = satellitesJSON.begin(); satellitesJSONObj != satellitesJSON.end(); ++satellitesJSONObj)
    // {
    //     satellitesNumber += 1;
    // }
    // Satellite satellitesArray[satellitesNumber]; // Define array of satellites (calling default constructor):
    // counter = 0;
    // for (json::iterator satellitesJSONObj = satellitesJSON.begin(); satellitesJSONObj != satellitesJSON.end(); ++satellitesJSONObj) // Set satellites details
    // {
    //     satellitesArray[counter].setFromJSONObj(satellitesJSONObj.key(), satellitesJSONObj.value());
    //     counter += 1;
    // }
    /* Create array of Satellite objects from input */
    int satellitesNumber;                                             // Total number of satellites
    Satellite *satellitesArray = getSatellites(argv[2], satellitesNumber); // TODO: Move tasksSatellites to vec?

    /* ============================= */
    /* Assign satellite to each task */
    // TODO: Move to function
    /* ============================= */
    int idx;
    for (int itTask = 0; itTask < tasksNumber; ++itTask)
    {
        idx = getIndexInt(priorityTasksArray, tasksNumber, itTask); // Get task index for each priority
        std::cout << "-- " << tasksArray[idx].taskId << " received" << std::endl;
        for (int itSatellite = 0; itSatellite < satellitesNumber; ++itSatellite)
        {
            if (checkResources(satellitesArray[itSatellite].resourcesInUse, tasksArray[idx].resources)) // Check if this satellite have resources available
            {
                for (auto i : tasksArray[idx].resources)
                {
                    satellitesArray[itSatellite].resourcesInUse.push_back(i); // Update resources in use
                }
                tasksArray[idx].assignedToSatelliteId = satellitesArray[itSatellite].satelliteId;
                std::cout << tasksArray[idx].taskId << " assigned to " << satellitesArray[itSatellite].satelliteId << std::endl;
                break;
            }
            else
            {
                std::cout << "Can't assign " << tasksArray[idx].taskId << " to " << satellitesArray[itSatellite].satelliteId << ", resources occupied " << std::endl;
            }
        }
    }

    /* Call task destructor */
    for (counter = 0; counter < tasksNumber; ++counter)
    {
        tasksArray[counter].~Task();
    }
    /* Call satellite destructor */
    for (counter = 0; counter < satellitesNumber; ++counter)
    {
        satellitesArray[counter].~Satellite();
    }

    // write prettified JSON to another file
    //std::ofstream o("pretty.json");
    //o << std::setw(4) << j << std::endl;
    return 0;
}
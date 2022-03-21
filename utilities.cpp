#include "taskManager.hpp"
#include "classSatellite.hpp" // Includes classTask.hpp

/* * * 
    getTasks( tasksInput, &tasksVec)
    --------------------------------

    -- Reads target tasks from JSON file.
    -- Initializes Task objects and pushes them into 
    the vector tasksVec.
    -- Ignores tasks from input that have already been
    completed.

 * * */
void getTasks(char *tasksInput, std::vector<Task> &tasksVec)
{
    std::cout << std::endl
              << "----- Reading tasks from " << tasksInput << " -----" << std::endl
              << std::endl;

    std::ifstream tasksInputFile(tasksInput); // Read tasks from file
    json tasksJSON;                           // Tasks to JSON object
    tasksInputFile >> tasksJSON;              //
    int counter = 0;
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        if (!taskJSONObj.value()["completed"]) // Ignore already completed tasks
        {
            tasksVec.push_back(Task());                                               // Initialize default task
            tasksVec[counter].setFromJSONObj(taskJSONObj.key(), taskJSONObj.value()); // Set each Task details
            ++counter;
        }
        else
        {
            std::cout << "- Ignoring " << taskJSONObj.key() << " because completed." << std::endl;
        }
    }
};

/* * * 
    getSatellites( satellitesInput, &satellitesVec)
    -----------------------------------------------

    -- Reads available satellites from JSON file.
    -- Initializes Satellite objects and pushes them into 
    the vector satellitesVec.
    -- Ignores satellites with status not IDLE.

 * * */
void getSatellites(char *satellitesInput, std::vector<Satellite> &satellitesVec)
{
    std::cout << std::endl
              << "----- Reading satellites from " << satellitesInput << " -----" << std::endl
              << std::endl;

    std::ifstream tasksInputFile(satellitesInput); // Read satellites from file
    json tasksJSON;                                // Satellites to JSON object
    tasksInputFile >> tasksJSON;                   //
    int satellitesNumber = tasksJSON.size();       // Total number of tasks
    int counter = 0;
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        if (taskJSONObj.value()["status"] == "IDLE")
        {
            satellitesVec.push_back(Satellite());
            satellitesVec[counter].setFromJSONObj(taskJSONObj.key(), taskJSONObj.value()); // Set each Task details
            ++counter;
        }
        else
        {
            std::cout << "- Ignoring " << taskJSONObj.key() << " because not IDLE." << std::endl;
        }
    }

    std::cout << "- List of available satellites:" << std::endl;
    for (auto satellite : satellitesVec)
    {
        std::cout << satellite.satelliteId << std::endl;
    }
}

/* * *
    sortTasksByPayoff( &tasksVec)
    ----------------------------

    -- Optimized bubbleSort to sort tasksVec by payoff

 * * */
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
                new_n = counter + 1;
            }
        }
        n = new_n;
    }

    std::cout << "- List of tasks to process (ordered by payoff):" << std::endl;
    for (auto task : tasksVec)
    {
        std::cout << task.taskId << " " << task.name << ", payoff = " << task.payoff << std::endl;
    }
}

/* * *
    checkResources( resourcesInUse, resourcesToUse)
    ----------------------------------------------

    -- Called by assignSatellitesToTasks(...), checks if
    the resources to use by a task are available in a specific
    satellite.
    
 * * */
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

/* * *
    assignSatellitesToTasks( &tasksVec, &satellitesVec)
    --------------------------------------------------

    -- Loops over tasks and satellites and, if resources 
    allow, assigns tasks to satellite. In particular,
    sets the attribute task.assignedToSatelliteId .
    
 * * */
void assignSatellitesToTasks(std::vector<Task> &tasksVec, std::vector<Satellite> &satellitesVec)
{
    std::cout << std::endl
              << "----- Assigning tasks to satellites "
              << " -----" << std::endl
              << std::endl;

    int tasksNumber = tasksVec.size();
    int satellitesNumber = satellitesVec.size();
    int itTask, itSatellite;

    for (auto &task : tasksVec) // Access element by reference to modify the vector permanently
    {
        for (auto &satellite : satellitesVec) // Access element by reference to modify the vector permanently
        {
            if (checkResources(satellite.resourcesInUse, task.resources)) // Check if this satellite have resources available
            {
                for (auto i : task.resources)
                {
                    satellite.resourcesInUse.push_back(i); // Update resources in use
                }
                task.assignedToSatelliteId = satellite.satelliteId; // Set satellite assigned to task
                break;
            }
        }
    }

    for (auto task : tasksVec) // Write summary to cout
    {
        if (task.assignedToSatelliteId != "undefined")
        {
            std::cout << task.taskId << " assigned to " << task.assignedToSatelliteId << std::endl;
        }
        else
        {
            std::cout << task.taskId << " could not been assigned, resources unavailable." << std::endl;
        }
    }
}

/* * * 
    writeTasks( tasksInput, tasksOutput, &tasksVec)
    --------------------------------

    -- Writes updated tasks to JSON file. In particular,
    it updates if each task has been completed (or not) and
    the event timers.

 * * */
void writeTasks(char *tasksInput, char *tasksOutput, std::vector<Task> &tasksVec)
{
    std::cout << std::endl
              << "----- Writting tasks to " << tasksOutput << " -----" << std::endl
              << std::endl;

    std::ifstream tasksInputFile(tasksInput); // Read tasks from file
    json tasksJSON;                           // Tasks to JSON object
    tasksInputFile >> tasksJSON;              //
    int tasksNumber = tasksJSON.size();       // Total number of tasks
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        for (auto task : tasksVec)
        {
            if (taskJSONObj.key() == task.taskId)
            {
                taskJSONObj.value()["completed"] = task.completed;
                taskJSONObj.value()["timeStart"] = task.timeStart;
                taskJSONObj.value()["timeEnd"] = task.timeEnd;
            }
        }
    }
    std::ofstream o(tasksOutput);
    o << std::setw(4) << tasksJSON << std::endl;

    std::cout << "- Done." << std::endl;
}

/* * * 
    writeSummary( &tasksVec, &satellitesVec)
    --------------------------------

    -- Writes summary of tasks results to cout.

 * * */
void writeSummary(std::vector<Task> &tasksVec, std::vector<Satellite> &satellitesVec)
{
    std::cout << std::endl
              << "----- Summary -----" << std::endl
              << std::endl;

    int numberTasks = tasksVec.size();
    int completedTasks = 0;
    for (auto task : tasksVec)
    {
        if (task.completed)
        {
            ++completedTasks;
        }
    }
    std::cout << "- Completed " << completedTasks << "/" << numberTasks << " tasks:" << std::endl;

    int tasksAssigned, tasksCompleted;
    for (auto satellite : satellitesVec)
    {
        tasksAssigned = 0;
        tasksCompleted = 0;
        for (auto task : tasksVec)
        {
            if (task.assignedToSatelliteId == satellite.satelliteId)
            {
                ++tasksAssigned;
                if (task.completed)
                {
                    ++tasksCompleted;
                }
            }
        }
        std::cout << satellite.satelliteId << " completed " << tasksCompleted << "/" << tasksAssigned << std::endl;
    }
}

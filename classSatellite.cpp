#include "taskManager.hpp"
#include "classSatellite.hpp"

/* Default constructor */
Satellite::Satellite()
{
    satelliteId = "undefined";
    status = "undefined";
    resourcesInUse = std::vector<int>();
};

/* Destructor */
Satellite::~Satellite()
{
    this->resourcesInUse = std::vector<int>(); // Release vector memory
};

/* Set satellite attributes from JSON object */
void Satellite::setFromJSONObj(std::string x, json y)
{
    satelliteId = x;
    status = y["status"];
};

/* Print satellite details */
void Satellite::print()
{
    std::cout << "===" << std::endl;
    std::cout << "satelliteID: " << this->satelliteId << std::endl;
    std::cout << "status: " << this->status << std::endl;
    std::cout << "resourcesInUse: [ ";
    for (auto resource : this->resourcesInUse) // Get task by reference so we modify the shared tasksVec
    {
        std::cout << resource << " ";
    }
    std::cout << "]" << std::endl
              << "===" << std::endl;
};

/* * *
    doTasks( &tasksVec)
    -------------------

    -- Method of Satellite, submits all the assigned tasks
    to each satellite.
    -- Takes tasksVec as reference to modify the assigned
    tasks by completed or not, and event timers.
    -- Usually called in parallel threads for each satellite,
    so using lock_guard to avoid data races.
    
 * * */
void Satellite::doTasks(std::vector<Task> &tasksVec)
{
    int probSuccess, durationTask;
    srand(time(NULL));
    auto time = std::chrono::system_clock::now();
    std::string timeStr;

    for (auto &task : tasksVec) // Get &task by reference so we modify the shared tasksVec
    {
        if (task.assignedToSatelliteId == this->satelliteId) //  Just do the tasks assigned to this satellite
        {

            time = std::chrono::system_clock::now(); // Get time task starts
            std::time_t timeOut = std::chrono::system_clock::to_time_t(time);
            timeStr = std::ctime(&timeOut);
            if (!timeStr.empty())
            {
                timeStr.pop_back();
                timeStr.pop_back(); // Remove endl from time string
            }

            {                                                    // lock_guard writting to cout to avoid data races
                std::lock_guard<std::mutex> guard(taskVecMutex); // lock_guard the writing of shared refere
                std::cout << this->satelliteId << " STARTED " << task.taskId << " at " << timeStr << std::endl;
            }
            task.timeStart = timeStr; // Keep task start time

            /* DOING THE ACTUAL TASKS */
            durationTask = rand() % 5;                                       // Random number between 0 and 4
            std::this_thread::sleep_for(std::chrono::seconds(durationTask)); // Simulate task process by sleeping
            probSuccess = rand() % 100;                                      // Random number between 0 and 99
            /* * * * * * * * * * * * */

            time = std::chrono::system_clock::now(); // Get time task ends
            timeOut = std::chrono::system_clock::to_time_t(time);
            timeStr = std::ctime(&timeOut);
            if (!timeStr.empty())
            {
                timeStr.pop_back();
                timeStr.pop_back(); // Remove endl from time string
            }

            if (probSuccess > 10) // Edit the task object with SUCCESS/FAIL
            {
                std::lock_guard<std::mutex> guard(taskVecMutex); // lock_guard the writing of shared reference to avoid writing race among threads
                task.completed = true;
                std::cout << this->satelliteId << " FINISHED (SUCCESS) " << task.taskId << " at " << timeStr << std::endl;
            }
            else
            {
                std::lock_guard<std::mutex> guard(taskVecMutex); // lock_guard the writing of shared reference to avoid writing race among threads
                std::cout << this->satelliteId << " FINISHED (FAIL) " << task.taskId << " at " << timeStr << std::endl;
            }
            task.timeEnd = timeStr; // Keep task end time
        }
    }
}

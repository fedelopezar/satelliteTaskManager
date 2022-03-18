#include "taskManager.hpp"
#include "classSatellite.hpp"

/* Default constructor */
Satellite::Satellite()
{
    satelliteId = "undefined";
    status = "undefined";
};

/* Destructor */
Satellite::~Satellite()
{
    this->resourcesInUse = std::vector<int>();
};

/* Set satellite from JSON object */
void Satellite::setFromJSONObj(std::string x, json y)
{
    satelliteId = x;
    status = y["status"];
};

/* Print task details */
void Satellite::print()
{
    std::cout << "===" << std::endl;
    std::cout << "satelliteID: " << this->satelliteId << std::endl;
    std::cout << "status: " << this->status << std::endl;
    std::cout << "===" << std::endl;
};

void Satellite::doTasks(std::vector<Task> &tasksVec)
{
    int probSuccess, durationTask;
    srand(time(NULL));
    auto time = std::chrono::system_clock::now();
    for (auto &task : tasksVec) // Get task by reference so we modify the shared tasksVec
    {
        if (task.assignedToSatelliteId == this->satelliteId) //  Just do the tasks assigned to this satellite
        {
            time = std::chrono::system_clock::now(); // Get time task starts
            std::time_t timeOut = std::chrono::system_clock::to_time_t(time);
            {
                std::lock_guard<std::mutex> guard(taskVecMutex); // lock_guard the writing of shared refere
                std::cout << this->satelliteId << " STARTED " << task.taskId << " at " << std::ctime(&timeOut);
            }

            // DOING THE ACTUAL TASKS //
            durationTask = rand() % 10; // Random number between 0 and 4
            std::this_thread::sleep_for(std::chrono::seconds(durationTask));
            probSuccess = rand() % 100; // Random number between 0 and 99
            // // // // // // // // // //

            time = std::chrono::system_clock::now(); // Get time task ends
            timeOut = std::chrono::system_clock::to_time_t(time);
            if (probSuccess > 20)
            {
                std::lock_guard<std::mutex> guard(taskVecMutex); // lock_guard the writing of shared reference to avoid writing race among threads
                task.completed = true;
                std::cout << this->satelliteId << " FINISHED (SUCCESS) " << task.taskId << " at " << std::ctime(&timeOut);
            }
            else
            {
                std::lock_guard<std::mutex> guard(taskVecMutex); // lock_guard the writing of shared reference to avoid writing race among threads
                std::cout << this->satelliteId << " FINISHED (FAIL) " << task.taskId << " at " << std::ctime(&timeOut);
            }
        }
    }
}
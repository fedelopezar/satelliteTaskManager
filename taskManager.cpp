#include "taskManager.hpp"
#include "classSatellite.hpp" // Includes classTask.hpp
#include "utilities.hpp"
std::mutex taskVecMutex; // Define global mutex

int main(int argc, char **argv)
{

    /* Create vector of objects Task from input */
    std::vector<Task> tasksVec;
    getTasks(argv[1], tasksVec);

    /* Sort tasks by payoff, from max to min */
    sortTasksByPayoff(tasksVec);

    /* Create array of Satellite objects from input */
    std::vector<Satellite> satellitesVec;
    getSatellites(argv[2], satellitesVec);

    /* Assign satellites to each task, if resources allow */
    assignSatellitesToTasks(tasksVec, satellitesVec);

    /* Submit tasks */
    std::cout << std::endl
              << "----- Submitting tasks -----" << std::endl
              << std::endl;
    std::vector<std::thread> vecOfThreads;
    for (auto satellite : satellitesVec) // Loop over satellites, each running in a parallel thread
    {
        // We need to ask explicity to send the reference tasksVec to each thread, because it is dangerous.
        // We are carefull by guarding data races with lock_guard.
        vecOfThreads.push_back(std::thread(&Satellite::doTasks, satellite, std::ref(tasksVec)));
    }
    for (std::thread &th : vecOfThreads) // Join the threads
    {
        if (th.joinable()) // Check if thread has not detached
            th.join();
    }

    /* Write the results of task processes */
    writeTasks(argv[1], argv[3], tasksVec);

    return 0;
}
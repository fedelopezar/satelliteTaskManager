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
    for (auto satellite : satellitesVec) // Loop doTasks over satellites, each runs in a parallel thread
    {
        // In the following, we need to explicity ask to send a reference because it is dangerous.
        // We take care guarding data races with lock_guard.
        vecOfThreads.push_back(std::thread(&Satellite::doTasks, satellite, std::ref(tasksVec)));
    }

    for (std::thread &th : vecOfThreads)
    {
        if (th.joinable()) // Check if thread has not detached
            th.join();
    }


    writeTasks( argv[1], argv[3], tasksVec);

    // write prettified JSON to another file
    //std::ofstream o("pretty.json");
    //o << std::setw(4) << j << std::endl;
    return 0;
}
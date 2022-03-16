#include "taskManager.hpp"
#include "classTask.hpp"
#include "classSatellite.hpp"
#include "utilities.hpp"


int main(int argc, char **argv)
{
    /* Create vector of objects Task uncompleted from input */
    std::vector<Task> tasksVec;
    getTasks(argv[1], tasksVec);

    /* Create array of task priorities, being 0 the maximum and tasksNumber the least */
    sortTasksByPayoff( tasksVec);

    /* Create array of Satellite objects from input */
    std::vector<Satellite> satellitesVec;
    getSatellites(argv[2], satellitesVec);

    /* Assign satellites to each task, if possible */
    assignSatellitesToTasks(tasksVec, satellitesVec);

    /* Submit tasks */


    // write prettified JSON to another file
    //std::ofstream o("pretty.json");
    //o << std::setw(4) << j << std::endl;
    return 0;
}
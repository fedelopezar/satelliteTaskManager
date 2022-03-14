#include "taskManager.hpp"
#include "classTask.hpp"
#include "classSatellite.hpp"

int main(int argc, char **argv)
{
    int counter;


    
    /* ============================ */
    /* Create array of Task objects */
    // TODO: Move to function
    /* ============================ */
    std::ifstream tasksInputFile(argv[1]); // Read tasks into json object
    json tasksJSON;
    tasksInputFile >> tasksJSON;
    int tasksNumber = 0; // Get number of tasks
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj)
    {
        tasksNumber += 1;
    }
    Task tasksArray[tasksNumber]; // Define array of tasks (calling default constructor):
    counter = 0;
    for (json::iterator taskJSONObj = tasksJSON.begin(); taskJSONObj != tasksJSON.end(); ++taskJSONObj) // Set tasks details
    {
        tasksArray[counter].setFromJSONObj(taskJSONObj.key(), taskJSONObj.value());
        tasksArray[counter].print();
        counter += 1;
    }



    /* ================================= */
    /* Create array of Satellite objects */
    // TODO: Move to function
    /* ================================= */
    std::ifstream satellitesInputFile(argv[2]);
    json satellitesJSON;
    satellitesInputFile >> satellitesJSON;
    int satellitesNumber = 0; // Get number of satellites
    for (json::iterator satellitesJSONObj = satellitesJSON.begin(); satellitesJSONObj != satellitesJSON.end(); ++satellitesJSONObj)
    {
        satellitesNumber += 1;
    }
    Satellite satellitesArray[satellitesNumber]; // Define array of satellites (calling default constructor):
    counter = 0;
    for (json::iterator satellitesJSONObj = satellitesJSON.begin(); satellitesJSONObj != satellitesJSON.end(); ++satellitesJSONObj) // Set satellites details
    {
        satellitesArray[counter].setFromJSONObj(satellitesJSONObj.key(), satellitesJSONObj.value());
        satellitesArray[counter].print();
        counter += 1;
    }



    // write prettified JSON to another file
    //std::ofstream o("pretty.json");
    //o << std::setw(4) << j << std::endl;
    return 0;
}
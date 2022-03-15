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
    std::cout << "Destructing satelliteID: " << this->satelliteId << std::endl;
    this->resourcesInUse = std::vector<int>();
};

/* Set satellite from JSON object      */
// TODO: redefine as constructor?
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
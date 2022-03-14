#include "taskManager.hpp"

class Satellite
{
public:
    std::string satelliteId;
    std::string status;
    Satellite(); // Default constructor
    //~Satellite(); // Destructor
    void setFromJSONObj(std::string x, json y);
    void print();
};
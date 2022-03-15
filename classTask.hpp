#include "taskManager.hpp"

class Task
{
public:
    std::string taskId;
    std::string name;
    std::vector<int> resources;
    double payoff;
    std::string assignedToSatelliteId;
    Task(); // Default constructor
    ~Task(); // Destructor
    void setFromJSONObj(std::string x, json y);
    void print();
};
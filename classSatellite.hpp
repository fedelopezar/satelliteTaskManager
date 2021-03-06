#include "taskManager.hpp"
#include "classTask.hpp"

class Satellite
{
public:
    std::string satelliteId;
    std::string status;
    std::vector<int> resourcesInUse;
    Satellite(); // Default constructor
    ~Satellite(); // Destructor
    void setFromJSONObj(std::string x, json y);
    void print();
    void doTasks(std::vector<Task> &tasksVec);
};
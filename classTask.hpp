#include "taskManager.hpp"

class Task
{
public:
    std::string taskId;
    std::string name;
    int *resources;
    double payoff;
    Task(); // Default constructor
    ~Task(); // Destructor
    void setFromJSONObj(std::string x, json y);
    void print();
};
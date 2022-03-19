extern void getTasks(char *tasksInput, std::vector<Task> &tasksVec);
extern void getSatellites(char *satellitesInput, std::vector<Satellite> &satellitesVec);
extern void sortTasksByPayoff(std::vector<Task> &tasksVec);
extern bool checkResources(std::vector<int> resourcesInUse, std::vector<int> resourcesToUse);
void assignSatellitesToTasks(std::vector<Task> &tasksVec, std::vector<Satellite> &satellitesVec);
void writeTasks(char *tasksInput, char *tasksOutput, std::vector<Task> &tasksVec);
void writeSummary(std::vector<Task> &tasksVec, std::vector<Satellite> &satellitesVec);

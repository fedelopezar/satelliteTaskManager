extern Task *getTasks(char *tasksInput, int &tasksNumber);
extern Satellite *getSatellites(char *satellitesInput, int &satellitesNumber);
extern int *getTasksPriorities(Task const *tasksArray, const int &tasksNumber);
extern int getIndexInt(int *array, int length, int value);
extern bool checkResources(std::vector<int> resourcesInUse, std::vector<int> resourcesToUse);
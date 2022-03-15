#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "include/json.hpp"
using json = nlohmann::json;

extern int getIndexInt(int *array, int length, int value);
extern bool checkResources(std::vector<int> resourcesInUse, std::vector<int> resourcesToUse);
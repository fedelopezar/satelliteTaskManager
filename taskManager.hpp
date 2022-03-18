#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <time.h>
#include <ctime>
#include "include/json.hpp"
using json = nlohmann::json;
extern std::mutex taskVecMutex; // Global mutex

#include "taskManager.hpp"

int getIndexInt(int *array, int length, int value)
{
    int i = 0;
    while (i < length && array[i] != value)
    {
        ++i;
    }
    return (i < length) ? i : 0 / 0;
}

bool checkResources(std::vector<int> resourcesInUse, std::vector<int> resourcesToUse)
{
    for (int i : resourcesToUse)
    {
        for (int j : resourcesInUse)
        {
            if (i == j)
                return false;
        }
    }
    return true;
}
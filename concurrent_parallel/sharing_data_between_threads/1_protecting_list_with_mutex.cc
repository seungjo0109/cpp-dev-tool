#include <list>
#include <mutex>
#include <algorithm>

std::list<int> list;
std::mutex some_mutex;

void AddToList(int value)
{
    std::lock_guard<std::mutex> lg(some_mutex);
    list.push_back(value);
}

bool ListContains(int value_to_find)
{
    std::lock_guard<std::mutex> lg(some_mutex);
    return std::find(list.begin(), list.end(), value_to_find) != list.end();
}
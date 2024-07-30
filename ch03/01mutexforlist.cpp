#include <list>
#include <mutex>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <thread>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

void insertElems()
{
    std::vector<int> nums{0, 1, 2, 3, 4, 5};
    for(auto& n : nums)
    {
        add_to_list(n);
        printf("insert Elem -- %d --\n", n);
    }
}

void findElems()
{
    std::vector<int> nums{5, 4, 3, 2, 1, 0};
    for(auto& n : nums)
    {
        if(list_contains(n))
            printf("find Elem -- %d --\n", n);
        else
            printf("Not find Elem -- %d --\n", n);
    }
}

int main()
{
    auto a = std::thread{insertElems};
    auto b = std::thread{findElems};
    b.join();
    a.join();
    printf("Program End ...\n");
    return 0;
}
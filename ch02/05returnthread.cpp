#include <thread>
#include <iostream>
// #include <chrono>

// std::thread f()
// {
//   void some_function();
//   return std::thread(some_function);
// }

// std::thread g()
// {
//   void some_other_function(int);
//   std::thread t(some_other_function, 42);
//   return t;
// }

void f(std::thread t);
std::thread g()
{
  void some_function();
  f(std::thread(some_function));
  std::thread t(some_function);
  return t;
}

int main()
{
  // std::cout << "Thread finished\n";

  return 0;
}
#include <iostream>
#include <thread>

struct func
{
  // 线程分离情况下，指向局部的变量不是一个好的主意
  int& i;
  func(int& i_) : i(i_) {}
  void operator()()
  {
    for (unsigned j = 0; j < 1000000; ++j)
    {
        ++i;
    }
  }
};

void f()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  try
  {
    // do_something_in_current_thread();
  }
  catch(const std::exception& e)
  {
    t.join();   // 确保线程被终止
    throw;
  }
  t.join();   // 确保线程被终止
}

int main() {
  f();
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
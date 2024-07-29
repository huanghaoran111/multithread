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

void oops()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  // my_thread.detach();   // 错误
  my_thread.join();   // 正确
}

int main()
{
  oops();
  // 可能没执行完
  //  std::cout << "some_local_state in main(): " << some_local_state << std::endl;
  return 0;
}
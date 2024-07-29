#include <iostream>
#include <thread>

class thread_guard
{
  std::thread& t;
public:
  explicit thread_guard(std::thread& t_) : t(t_) {}
  ~thread_guard()
  {
    // 在任何执行线程上，join()只能被调用一次，假若线程已经汇合过，那么再次调用join()则是错误行为
    if (t.joinable())
    {
      t.join();
    }
  }
  thread_guard(const thread_guard&) = delete;
  thread_guard& operator=(const thread_guard&) = delete;
};

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
  thread_guard g(t);
  // do_something_in_current_thread();
}

int main()
{
  std::thread t(f);
  thread_guard g(t);
  // do other things
  return 0;
}
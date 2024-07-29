#include <thread>


class scoped_thread
{
  std::thread t;
public:
  explicit scoped_thread(std::thread t_) :
    t(std::move(t_))
  {
    if (!t.joinable()) // 检查是否成功创建线程
      throw std::logic_error("No thread");
  }
  ~scoped_thread()
  {
    t.join(); // 等待线程结束
  }
  scoped_thread(const scoped_thread&) = delete;
  scoped_thread& operator=(const scoped_thread&) = delete;
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
  int some_local_state;
  scoped_thread t{std::thread(func(some_local_state))};
  // do_something_in_current_thread();
}

int main()
{
  scoped_thread t();
  
  return 0;
}
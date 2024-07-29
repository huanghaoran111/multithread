#include <thread>

void do_work(unsigned id);
void f()
{
  std::vector<std::thread> threads;
  for(unsigned i = 0; i < 20; ++i)
  {
    threads.emplace_back(do_work, i);
  }
  for(auto& t : threads)
  {
    t.join();
  }
}


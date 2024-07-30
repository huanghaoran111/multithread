#include <string>
#include <mutex>


class some_data
{
    int a;
    std::string b;
public:
    void do_something();
};

class data_warpper
{
private:
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func)
    {
        std::lock_guard<decltype(m)> l(m);
        func(data);
    }
};  

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
    unprotected = &protected_data;
}

data_warpper x;

void foo()
{
    x.process_data(malicious_function);     // 传入恶意函数
    unprotected->do_something();            // 以无保护方式访问本应受保护的共享数据
}

#include <iostream>
#include <functional>
#include <assert.h>

class hello
{
public:
    void f(int a)
    {
        std::cout << "f: " << a << std::endl;
    }
    virtual void ff(int a)
    {
        std::cout << "ff: " << a << std::endl;
    }

    int fff(char a)
    {
        std::cout << "fff: " << a << std::endl;
        return 0;
    }
};

template <typename T, T t>
class Callback;

template <typename T, typename Ret, typename... Args, Ret (T::*mf)(Args...)>
class Callback<Ret (T::*)(Args...), mf>
{
public:
    typedef Ret (*callback_func)(Args...);

    static Ret call(Args... args) { return func(args...); }
    static callback_func set(T *obj)
    {
        func = [obj](auto &&...args) -> decltype(auto)
        { return (obj->*mf)(std::forward<decltype(args)>(args)...); };
        return static_cast<callback_func>(call);
    }

private:
    static std::function<Ret(Args...)> func;
};

template <typename T, typename Ret, typename... Args, Ret (T::*mf)(Args...)>
std::function<Ret(Args...)> Callback<Ret (T::*)(Args...), mf>::func;

struct LibStruct
{
    int (*callback)(char) = nullptr;
    void (*callback2)(int) = nullptr;
};

int main(int, char **)
{
    hello obj;

    Callback<decltype(&hello::f), &hello::f>::set(&obj);
    Callback<decltype(&hello::f), &hello::f>::call(0);

    Callback<decltype(&hello::ff), &hello::ff>::callback_func func = Callback<decltype(&hello::ff), &hello::ff>::set(&obj);
    func(1);

    LibStruct vendor;
    Callback<decltype(&hello::fff), &hello::fff> my_proxy;
    vendor.callback = my_proxy.set(&obj);

    vendor.callback('b');

    // Preffered method
    vendor.callback2 = Callback<decltype(&hello::f), &hello::f>::set(&obj);

    vendor.callback2(2);
}

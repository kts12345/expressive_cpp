// Expressive c++. 06. Fun With Fucntion Composition

namespace xpcpp {
    
template<typename... FnN> struct compose_fn;

template <typename Fn1, typename... FnN>
struct compose_fn <Fn1, FnN...>
{
    explicit compose_fn(Fn1 f1, FnN... fn) : fn1(f1), fnN(fn...) {}
    
    Fn1 fn1;
    compose_fn<FnN...> fnN;
    
    template <typename T>
    auto operator() (T x) const { return fn1(fnN(x)); }
};

template <> struct compose_fn<>
{
    template <typename T>
    auto operator() (T x) const { return x; }
};

template <typename Fn1, typename... FnN>
auto compose(Fn1 f1, FnN... fn) { return compose_fn<Fn1, FnN...>(f1, fn...); };

} // end of xpcpp

#include <iostream>
#include <boost/phoenix.hpp>
using boost::phoenix::arg_names::arg1;

auto inc    = [](auto x) { return x + 1; };
auto square = [](auto x) { return x * x; };
float normal_fn(int x) { return (float)(x*x);};
auto inc2 = arg1+2;

auto composed_fn = xpcpp::compose(inc, square, inc2, square);

int main()
{
  std::cout << composed_fn(3) << std::endl;
}

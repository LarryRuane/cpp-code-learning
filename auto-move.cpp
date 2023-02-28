// g++ -O2 -std=c++17 auto-move.cpp && ./a.out
//
// Trying to figure out if passing an object (in particular, a container) by
// value to a function, and that object is not referenced after that in
// the caller, is the compiler smart enough to automatically insert a
// std::move()?
//
// Answer: it isn't (which I think is a good thing).

#include <iostream>
#include <vector>
#include <map>

int main()
{
    std::map<int, std::vector<int>> m;
    std::vector<int> v{25,3};
    std::cout << &v[0] << '\n';
    //m.emplace(2, v);
    m.emplace(2, std::move(v));
    std::cout << "if the following address is different, then a copy occurred\n";
    std::cout << &m[2][0] << '\n';
}

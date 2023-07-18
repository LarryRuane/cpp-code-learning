// g++ -g3 -std=c++17 derived-class.cpp
// This is like CScriptBase (A) and CScript (B)
#include <iostream>
#include <string.h>

template <typename T>
struct A {
    T x{4};
    A(T _x) : x(_x) {};
    const T GetX() { return x;}
    void SetX(T s) { x = s; }
private:
// Allow B to access y even though private
// (not just derived classes, but any class containing
// variables of this class A).
friend class B;
    int y;
};

// either of these works the same:
//typedef struct A<int> TD;
using TD = struct A<int>;

// If this says "private TD" then "b.GetX()" in main doesn't compile,
// because all of TD's methods are private within B.
// "public" is the default ("struct B : TD" is the same as public).
// Note this can also say "public A<int>".
struct B : public TD {
    // this also works: B(int x) : A<int>(x) {};
    B(int x) : A(x) {y = 7;};
    void inc(int i) { SetX(GetX() + i); }
};

int main()
{
    B b(2);
    b.inc(10);
    std::cout << b.GetX() << '\n';
    return 0;
}
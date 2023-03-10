// g++ -g3 -std=c++17 chained-methods.cpp
#include <iostream>
#include <string.h>

class chain {
private:
    int m_i;
public:
    explicit chain(int init_i) : m_i(init_i) {};
    explicit chain() : m_i(0) {};

    chain& add(int a) {
        m_i += a;
        return *this;
    }

    chain& multiply(int m) {
        m_i *= m;
        return *this;
    }

    chain add_ret_new_object(int a) const {
        chain c_new{*this};
        c_new.m_i += a;
        return c_new; // moved, I think
    }

    int get() const { return m_i; }

    const chain& freeze() const { return *this; };
};

int main()
{
    std::cout << chain(2).add(1).multiply(2).add(10).get() << '\n';
    std::cout << chain(2).add(1).freeze().get() << '\n';

    // this doesn't compile because you can't mutate a frozen object
    // std::cout << chain(2).add(1).freeze().add(2).get() << '\n';

    // not really frozen because we made a copy
    chain not_frozen{chain(2).add(1).freeze()};
    not_frozen.add(2);

    // this doesn't compile because it's a non-const reference
    // chain& frozen{chain(2).add(1).freeze()};

    // this compiles
    const chain& frozen{chain(2).add(1).freeze()};

    // not allowed, tries to mutate the object
    // frozen.add(2);

    chain c{chain(1)};
    std::cout << "c expect 1: " << c.get() << '\n';
    chain c_copy{c.add(1)};
    std::cout << "add 1, c_copy expect 2: " << c_copy.get() << '\n';
    chain& c_ref{c.add(8)};
    std::cout << "c.add(8), c_ref expect 10: " << c_ref.get() << '\n';
    std::cout << "c expect 10: " << c.get() << '\n';
    chain c_new{c.add_ret_new_object(4)};
    std::cout << "c_new expect 10+4: " << c_new.get() << '\n';

    c.add(5);
    std::cout << "c added 5, expect 15: " << c.get() << '\n';
    std::cout << "c_copy expect 2: " << c_copy.get() << '\n';
    std::cout << "c_ref, expect 15: " << c_ref.get() << '\n';

    return 0;
}

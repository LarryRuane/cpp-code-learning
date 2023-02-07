// https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
// g++ -std=c++17

class Foo
{
public:
    // single parameter constructor, can be used as an implicit conversion
    explicit Foo (int foo) : m_foo (foo) {}
    int GetFoo() { return m_foo; }
private:
    int m_foo;
};

void DoBar(Foo foo) {
    int i = foo.GetFoo();
}

int main()
{
    // this doesn't compile because of the 'explicit' above
    //DoBar(42);

    // this does work (with the explicit):
    DoBar(Foo(42));

    // my comment: explicit should be the norm, compiler
    // is trying too hard to make it easy to write code
    // at the expense of readability (if I only look at
    // the call site, I'd like to know that this takes
    // a Foo object, not an int)
    return 0;
}

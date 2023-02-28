// g++ -g3 -std=c++17 copy-move-cons.cpp
#include <iostream>
#include <string.h>

int line;

// This class demonstrates the seven "essential operations";
// see chapter 6 of A Tour of C++
class String {
public:
    char* m_buffer;
    size_t m_size;

    // default cons - reasonable default is an empty string
    String() : m_size(0), m_buffer(new char[1]{'\0'}) {
        std::cout << line << " default constructor " << intptr_t(m_buffer) << "\n";
    }
    // copy cons
    String(const char* string) {
        m_size = strlen(string);
        m_buffer = new char[m_size+1];
        strcpy(m_buffer, string);
        std::cout << line << " constructor from char* " << m_buffer << " " << intptr_t(m_buffer) << "\n";
    }
    // copy cons - make new object independent of the source object
    String(const String& other) {
        m_size = other.m_size;
        m_buffer = new char[m_size+1];
        strcpy(m_buffer, other.m_buffer);
        std::cout << line << " constructor from other " << m_buffer << " " << intptr_t(m_buffer) << "\n";
    }
#if 1
    // move cons - we're allowed to "hollow out" the argument since it's temporary
    // (there's no danger, this won't be called if other isn't an rvalue)
    String(String&& other) {
        m_size = other.m_size;
        m_buffer = other.m_buffer; // copy just the pointer!
        // must make other a valid minimal String object that can be destructed
        other.m_size = 0;
        other.m_buffer = new char[1]{'\0'};
        std::cout << line << " move from other " << m_buffer << " " << intptr_t(m_buffer) << "\n";
    }
#endif
    // copy assignment - clean up destination, then copy from source
    String& operator=(const String& other) {
        delete[] m_buffer;
        m_size = other.m_size;
        m_buffer = new char[m_size+1];
        strcpy(m_buffer, other.m_buffer);
        std::cout << line << " assignment from other " << m_buffer << " " << intptr_t(m_buffer) << "\n";
        return *this;
    }
    // move assignment - clean up destination, then steal from source
    String& operator=(String&& other) {
        delete[] m_buffer;
        m_size = other.m_size;
        m_buffer = other.m_buffer;
        // must make other a valid minimal String object that can be destructed
        other.m_size = 0;
        other.m_buffer = new char[1]{'\0'};
        std::cout << line << " move assignment from other " << m_buffer << " " << intptr_t(m_buffer) << "\n";
        return *this;
    }
    ~String() {
        std::cout << line << " delete " << m_buffer << " " << intptr_t(m_buffer) << "\n";
        delete[] m_buffer;
    }
};

class UsesString {
public:
    String s;
    UsesString(const String& s_arg) : s(s_arg) {}
    UsesString(String&& s_arg) : s(std::move(s_arg)) {}
};

int main()
{
    line = __LINE__; String s = "hello";
    line = __LINE__; String d;
    line = __LINE__; String a{"hi"};
    line = __LINE__; String b = s;
    line = __LINE__; String c{s};
    std::cout << "---- need to make a copy, because e remains in-scope\n";
    line = __LINE__; UsesString us_copy(c);
    std::cout << "---- construct from a string, but then move, NOT make a useless copy\n";
    std::cout << "---- comment out the String move cons and see it make an extra copy\n";
    line = __LINE__; UsesString us_move(String("to-UsesString"));
    line = __LINE__; b = a;
    line = __LINE__; s = std::move(b);
    std::cout << "---- moved-from b (should be empty string) :" << b.m_buffer << ":\n";
    std::cout << "---- about to reach end of main()\n";
    line = __LINE__;
    auto i = std::hash<std::string>{}("hello");
    std::cout << i << '\n';
}
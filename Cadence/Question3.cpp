#define STRING_H

#include <cstring>
#include <stdlib.h> // C standard library header (also works in C++)

class string
{
public:

    string();
    ~string();

    string(char* letters);    // ISSUE: Should be const char* to allow string literals
    string(string const& rhs);

    string& operator=(char* letters);    // ISSUE: Should be const char* to allow string literals
    string& operator=(string rhs);    // ISSUE: Should be const reference (string const&) for efficiency

    void append(char* letters);    // ISSUE: Should be const char* to allow string literals
    size_t length();    // ISSUE: Should be const member function

    bool is_empty();    // ISSUE: Should be const member function
    void empty();

    char* c_str()    // ISSUE: Should be const member function returning const char*
    {
        return m_szchars;
    }

    char* m_szchars;    // ISSUE: Should be private member variable
    int f_count_;    // ISSUE: Should be private member variable, and should be size_t type

};

string::string()
    : f_count_{ 0 }
{
    m_szchars = 0;    // ISSUE: Should initialize to nullptr instead of 0
}

string::~string()
{
    free(m_szchars);    // ISSUE: Used free() but allocated with new[] - should use delete[]
}

string::string(char* letters)
{
    f_count_ = strlen(letters);
    m_szchars = new char[f_count_];    // ISSUE: Buffer too small - need +1 for null terminator
    for (int i = 0; i < f_count_; ++i)
    {
        m_szchars[i] = letters[i];
    }
    // ISSUE: Missing null terminator at end of string
}

string::string(string const& rhs)
{
    f_count_ = strlen(rhs.m_szchars);    // ISSUE: Using strlen on potentially null pointer
    m_szchars = new char[f_count_];    // ISSUE: Buffer too small - need +1 for null terminator
    for (int i = 0; i < f_count_; ++i)
    {
        m_szchars[i] = rhs.m_szchars[i];
    }
    // ISSUE: Missing null terminator at end of string
}
// ISSUE: Missing implementation for operator=, append, length, is_empty, empty functions
// ISSUE: No swap function to implement copy-and-swap idiom
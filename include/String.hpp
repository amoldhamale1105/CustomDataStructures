#pragma once

#include <Vector.hpp>
#include <stddef.h>
#include <string.h>
#include <stdexcept>
#include <ostream>
#include <istream>

class String
{
    size_t m_count, m_maxSize;
    char* m_data;

public:
    String();
    String(const char& ch);
    String(const char* data);
    String(const String& other);
    String(String&& other) noexcept;
    virtual ~String();

    void append(const char& ch);
    void prepend(const char& ch);
    void clear();
    void reverse();
    Vector<String> split(const char& delim = ',');
    void trim(const char& ch = ' ', const bool& leading = true, const bool& trailing = true, const bool& middle = false);
    String substr(const size_t& pos = 0, const size_t& len = SIZE_MAX);
    size_t length() const;
    char front() const;
    char back() const;
    char* data() const;
    const char* c_str() const;
    char at(const size_t& index) const;
    bool empty() const;
    
    String operator+(const String& str);
    void operator+=(const String& str);
    bool operator==(const String& str);
    bool operator!=(const String& str);
    bool operator<(const String& str);
    bool operator>(const String& str);
    char& operator[](const size_t& index);
    void operator=(const String& other);

    friend std::ostream& operator<<(std::ostream& stream, const String& str);
    friend std::istream& operator>>(std::istream& stream, String& str);
};
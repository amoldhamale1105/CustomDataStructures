#pragma once

#include <stddef.h>
#include <string.h>
#include <stdexcept>
#include <ostream>

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
    bool operator<(const String& str);
    bool operator>(const String& str);
    char& operator[](const size_t& index);
    void operator=(const String& other);

    friend std::ostream& operator<<(std::ostream& stream, const String& str);
};
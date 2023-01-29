#include "String.hpp"

String::String() : m_count(0), m_maxSize(m_count+1), m_data(nullptr)
{
}

String::String(const char &ch) : m_count(1), m_maxSize(m_count+1), m_data(new char[m_maxSize])
{
    m_data[0] = ch;
    m_data[1] = '\0';
}

String::String(const char *data) : m_count(strlen(data)), m_maxSize(m_count+1), m_data(new char[m_maxSize])
{
    strncpy(m_data, data, m_count);
    m_data[m_count] = '\0';
}

String::String(const String &other) : m_count(other.m_count), m_maxSize(other.m_maxSize), m_data(new char[m_maxSize])
{
    strncpy(m_data, other.m_data, m_count);
    m_data[m_count] = '\0';
}

String::String(String &&other) noexcept : m_count(other.m_count), m_maxSize(other.m_maxSize), m_data(other.m_data)
{
    other.m_data = nullptr;
    other.m_count = 0;
    other.m_maxSize = m_count+1;
}

String::~String()
{
    if (m_data != nullptr)
        delete [] m_data;
}

void String::append(const char &ch)
{
    if (m_count == m_maxSize-1){
        char* oldData = m_data;
        m_maxSize *= 2;
        m_data = new char[m_maxSize];

        if (oldData != nullptr){
            strncpy(m_data, oldData, m_maxSize/2);
            delete [] oldData;
        }
    }

    m_data[m_count] = ch;
    m_data[m_count+1] = '\0';
    m_count++;
}

void String::prepend(const char &ch)
{
    if (m_count == m_maxSize-1){
        char* oldData = m_data;
        m_maxSize *= 2;
        m_data = new char[m_maxSize];

        if (oldData != nullptr){
            strncpy(m_data, oldData, m_maxSize/2);
            delete [] oldData;
        }
    }
    for(auto i = m_count+1; i > 0; i--)
    {
        m_data[i] = m_data[i-1];
    }
    
    m_data[0] = ch;
    m_data[m_count+1] = '\0';
    m_count++;
}

void String::clear()
{
    m_count = 0;
}

void String::reverse()
{
    if (m_count < 1 || m_data == nullptr)
        return;

    size_t mid = m_count/2;
    for(auto i = 0; i < mid; i++)
    {
        char temp = m_data[i];
        m_data[i] = m_data[m_count-i-1];
        m_data[m_count-i-1] = temp;
    }
}

Vector<String> String::split(const char &delim)
{
    Vector<String> stringList;
    size_t prev{0}, curr{0};

    while (curr < m_count)
    {
        if (*(m_data+curr) == delim || curr == m_count-1){
            if (*(m_data+prev) != delim){
                char part[curr-prev+2];
                strncpy(part, m_data+prev, curr-prev+1);
                part[curr-prev+1] = '\0';
                stringList.push_back(part);
            }
            prev = curr+1;
        }
        curr++;
    }
    
    return stringList;
}

void String::trim(const char &ch, const bool &leading, const bool &trailing, const bool &middle)
{
    if (m_count == 0)
        return;
    
    size_t curr{0};
    
    if (leading && m_data[0] == ch){
        size_t trimCount{0};
        while (*(m_data+trimCount) == ch)
        {
            trimCount++;
        }
        strncpy(m_data, m_data+trimCount, m_count-trimCount);
        m_count -= trimCount;
    }
    if (middle){
        curr = 0;
        while (*(m_data+curr) == ch)
        {
            curr++;
        }
        size_t trimCount{0};
        while (curr < m_count)
        {
            if (*(m_data+curr) == ch)
                trimCount++;
            else{
                if (trimCount > 0){
                    strncpy(m_data+curr-trimCount, m_data+curr, strlen(m_data+curr));
                    m_count -= trimCount;
                    curr -= trimCount;
                    trimCount = 0;
                }
            }
            curr++;
        }
    }
    if (trailing && m_data[m_count-1] == ch){
        curr = m_count;
        while (m_data[curr-1] == ch)
        {
            curr--;
        }
        m_count = curr;
    }
    
    m_data[m_count] = '\0';
}

size_t String::length() const
{
    return m_count;
}

char String::front() const
{
    return m_data != nullptr && m_count > 0 ? m_data[0] : '\0';
}

char String::back() const
{
    return m_data != nullptr && m_count > 0 ? m_data[m_count-1] : '\0';
}

char *String::data() const
{
    return m_count > 0 ? m_data : nullptr;
}

const char *String::c_str() const
{
    return m_count > 0 ? static_cast<const char*>(m_data) : nullptr;
}

char String::at(const size_t &index) const
{
    return m_data != nullptr && index < m_count ? m_data[index] : '\0';
}

bool String::empty() const
{
    return m_data == nullptr || m_count == 0;
}

String String::operator+(const String &str)
{
    String concatStr;
    concatStr.m_count = m_count + str.m_count;
    concatStr.m_maxSize = concatStr.m_count + 1;
    concatStr.m_data = new char[concatStr.m_maxSize];
    
    strncpy(concatStr.m_data, m_data, m_count);
    strncpy(concatStr.m_data+m_count, str.m_data, str.m_count);
    concatStr.m_data[concatStr.m_count] = '\0';

    return concatStr;
}

void String::operator+=(const String &str)
{
    if (m_maxSize <= (m_count + str.m_count)){
        char* oldData = m_data;
        size_t oldMax = m_maxSize;
        m_maxSize = m_count + str.m_count + 1;
        m_data = new char[m_maxSize];

        if (oldData != nullptr){
            strncpy(m_data, oldData, oldMax);
            delete [] oldData;
        }
    }
    strncpy(m_data+m_count, str.m_data, str.m_count);
    m_count += str.m_count;
    m_data[m_count] = '\0';
}

bool String::operator==(const String &str)
{
    return strncmp(m_data, str.m_data, m_count) == 0;
}

bool String::operator<(const String &str)
{
    return strncmp(m_data, str.m_data, m_count) < 0;
}

bool String::operator>(const String &str)
{
    return strncmp(m_data, str.m_data, m_count) > 0;
}

char &String::operator[](const size_t &index)
{
    return m_data != nullptr && index < m_count ? m_data[index] : throw std::out_of_range("index out of range");
}

void String::operator=(const String &other)
{
    if (m_maxSize <= other.m_count){
        delete [] m_data;
        m_maxSize = other.m_count + 1;
        m_data = new char[m_maxSize];
    }
    strncpy(m_data, other.m_data, other.m_count);
    m_count = other.m_count;
    m_data[m_count] = '\0';
}

std::ostream& operator<<(std::ostream& stream, const String& str)
{
    stream << (str.empty() ? "" : str.c_str());
    return stream;
}

std::istream &operator>>(std::istream &stream, String &str)
{
    char buf[256];
    memset(buf, 0, sizeof buf);
    stream.getline(buf, sizeof buf);
    str = buf;
    return stream;
}

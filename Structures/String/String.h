#pragma once
#include <iostream>

class String{
    
    char* data;
    size_t capacity;
    size_t size;

    void free();
    void copy(const String& other);
    void resize(size_t newCapacity);

    public:
    String();
    String(const char* string);
    String(const String& other);
    String& operator=(const String& other);
    String(String&& other) noexcept;          
    String& operator=(String&& other) noexcept;
    ~String(); 
    
    const char* c_str() const;
    String& operator+=(const String& other);
    size_t getSize() const;
    size_t getCapacity() const;
    char& operator[](unsigned index);
    const char& operator[] (unsigned index) const;
    String substr(unsigned start, unsigned length);


    friend String operator+(const String& str1, const String& str2);
    friend std::ostream& operator<<(std::ostream& os, const String& string);
    friend std::istream& operator>>(std::istream& is, String& string);
    String toString() const;
    
};

bool operator==(const String& str1, const String& str2);
bool operator!=(const String& str1, const String& str2);
bool operator<(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
bool operator>=(const String& str1, const String& str2);
bool operator<=(const String& str1, const String& str2);
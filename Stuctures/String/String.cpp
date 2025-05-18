#include "String.h"
#include <algorithm>
#include <cstring>
#pragma warning (disable 4996)
    String::String() : data(new char[1]), size(0), capacity(0) {data[0]='\0';};
    String::String(const char* m_data){
        size = strlen(m_data);
        capacity = size + 1;
        data = new char[capacity];
        strcpy(data,m_data);
    } 
    void String::copy(const String& other){
        size = other.size;
        capacity = other.capacity;
        data = new char[capacity];
        strcpy(data,other.data);
    }
    String::String(const String& other){
        copy(other);
    }
    void String::free(){
        delete [] data;
    }
    String& String::operator=(const String& other){
        if(this!=&other){
            free();
            copy(other);
        }
        return *this;
    }
    
    String::String(String&& other) noexcept: data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
    }

    String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        free();  
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
    }
    String::~String(){
        free();
    }
    void String::resize(size_t newCapacity){
        char* newData = new char [newCapacity+1];
        strcpy(newData,data);
        delete []data;
        data = newData;
        capacity = newCapacity;
    }
    const char* String::c_str() const{
        return data;
    }
    String& String::operator+=(const String& other) {
        if (other.size == 0) {return *this;}
        if (size + other.size + 1 > capacity){resize(size + other.size + 1);}
        strcat(data, other.data);
        size += other.size;
        return *this; 
    }
    size_t String::getSize() const{return size;}
    size_t String::getCapacity() const{return capacity;}
    char& String::operator[] (unsigned index){
        return data[index];
    }
    const char& String::operator[](unsigned index) const{
        return data[index];
    }
    String String::substr(unsigned start, unsigned length) {
        if (start + length > size){return String("");}
        char* sub = new char[length + 1];
        for (unsigned i = 0; i < length; ++i){
            sub[i] = data[start + i];
        }
        sub[length] = '\0';
        String result(sub);
        delete[] sub;
        return result;
    }
    String operator+(const String& str1, const String& str2){
        String result(str1);
        result += str2;
        return result;
    }
    std::ostream& operator<<(std::ostream& os, const String& string){
        return os<<string.data;
    }
    std::istream& operator>>(std::istream& is,String& string){
        char buffer[1024];
        is>>buffer;
        string.size = strlen(buffer);
        if(string.capacity <= string.size){
            string.resize(string.size + 1);
        }
        strcpy(string.data, buffer);
        return is;

    }

    bool operator==(const String& lhs, const String& rhs) {return strcmp(lhs.c_str(), rhs.c_str()) == 0;}
    bool operator!=(const String& lhs, const String& rhs) {return !(lhs == rhs);}
    bool operator>(const String& lhs, const String& rhs)  {return strcmp(lhs.c_str(), rhs.c_str()) > 0;}
    bool operator>=(const String& lhs, const String& rhs) {return strcmp(lhs.c_str(), rhs.c_str()) >= 0;}
    bool operator<(const String& lhs, const String& rhs)  {return strcmp(lhs.c_str(), rhs.c_str()) < 0;}
    bool operator<=(const String& lhs, const String& rhs) {return strcmp(lhs.c_str(), rhs.c_str()) <= 0;}



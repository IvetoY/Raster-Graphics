#include "String.h"
#include <algorithm>
#include <cstring>
#pragma warning (disable 4996)
    String::String() : data(nullptr), size(0), capacity(0){};
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
    /*String& String::operator+=(const String& other){
        if(size + other.size + 1 > capacity){
            return ;
        }
    }*/
    size_t String::getSize() const{return size;}
    size_t String::getCapacity() const{return capacity;}
    char& String::operator[] (unsigned index){
        return data[index];
    }
    const char& String::operator[](unsigned index) const{
        return data[index];
    }
    /*String String::substr(unsigned start, unsigned length){
        if((start + length ) > size ) {return String("");}

    }*/
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
            //resize(string.size + 1);
        }
        strcpy(string.data, buffer);
        return is;

    }



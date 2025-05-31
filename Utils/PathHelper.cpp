
#include <iostream>
#include <cstring>
#include "PathHelper.h"

const char* extractFileExtension(const char* filePath){
    size_t filePathLength = strlen(filePath);
    if(!filePath) {return nullptr;}
    if(filePathLength==0) {return nullptr;}
    const char* end = filePath + filePathLength - 1;
    const char* iterator = end;
    while(filePathLength>0 && *iterator!='.'){
        iterator --;
        filePathLength --;
    }
    if(filePathLength == 0){return "";}
    return iterator;
}

std::string normalizePath(const std::string& path) {
    return std::filesystem::path(path).lexically_normal().string();
}
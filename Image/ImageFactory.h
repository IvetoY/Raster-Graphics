#pragma once
#include "Image.h"
#include "PBM.h"
#include "PGM.h"
#include "PPM.h"
#include <string>
#include <fstream>
#include <cstring>
class ImageFactory{
public:
    static Image* create(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file){return nullptr;}
        
        std::string magicNumber;
        file >> magicNumber;
        file.close();
        
        if (magicNumber == "P3" || magicNumber == "P6") {return new PPM(filePath);}
        else if (magicNumber == "P2" || magicNumber == "P5"){return new PGM(filePath);}
        else if (magicNumber == "P1" || magicNumber == "P4"){return new PBM(filePath);}
        return nullptr;
    }

    static void destroy(Image* img) {delete img;}

};
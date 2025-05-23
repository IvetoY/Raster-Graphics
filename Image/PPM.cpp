#include "PPM.h"
#include "Image.h"
#include "../Pixel/Pixel.h"
#include <fstream>
#include <stdexcept>
PPM::~PPM(){free();}
PPM::PPM() : Image(), format(Format::P3_ASCII){magicNumber = "P3";}

PPM::PPM(const String& fileName){load(fileName);}

PPM::PPM(const PPM& other) : 
    Image(other), format(other.format) {
}
PPM& PPM::operator=(const PPM& other)
{
    if (this != &other){
        free();
        copy(other);
        Image::operator=(other);
    }
    return *this;
}
PPM& PPM::operator=(PPM&& other) noexcept
{
    if (this != &other){
        free();
        copy(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}
PPM::PPM(const PPM& other) : Image(other){copy(other);}
PPM::PPM(PPM&& other) noexcept : Image(std::move(other)){move(std::move(other));}

PPM::PPM(unsigned _width, unsigned _height, uint8_t _maxColour, const String& _magicNum, const String& _fileName, const std::vector<std::vector<Pixel>>& _pixels, Format _format = P3_ASCII): 
    Image(_width, _height, _maxColour, _magicNum, _fileName, _pixels), format(_format) {}
PPM* PPM::clone() const {
    return new PPM(*this);
}

void PPM::load(const String& filename){
    std::ifstream file(filename.c_str());
    if(!file){throw std::runtime_error(("Failed to open file: " + filename).c_str());}

    //get the magic number

    if(magicNumber!= "P3" && magicNumber!="P6"){throw std::runtime_error("Invalid PPM format");}
    if(magicNumber == "P3"){format = P3_ASCII;}
    else {format = P6_BINARY;}
    
    //to be done
}
Image* PPM::collage(const Image* second, const String& newFileName)const{
    return second->collageWithPPM(this, newFileName);
}

Image* PPM::collageWithPBM(const PBM* second, const String& newFileName) const{throw std::logic_error("Can't collage different types!");}

Image* PPM::collageWithPGM(const PGM* second, const String& newFileName) const{throw std::logic_error("Can't collage different types!");}

Image* PPM::collageWithPPM(const PPM* second, const String& newFileName) const{

}


void PPM::free(){
    pixels.clear();
}

void PPM::move(PPM&& other) noexcept {
    pixels = std::move(other.pixels);
    other.pixels.clear();
    
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = std::move(other.magicNumber);
    fileName = std::move(other.fileName);
    format = other.format;

    other.width = 0;
    other.height = 0;
    other.maxColourNumbers = 0;
    other.format = P3_ASCII;  
}

void PPM::copy(const PPM& other) {
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = other.magicNumber;
    fileName = other.fileName;
    format = other.format;
    pixels = other.pixels; 
} 
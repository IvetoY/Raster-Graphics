#include "PBM.h"
#include "Image.h"
PBM::PBM() : Image(), format(P1_ASCII), pixels(nullptr) {}

PBM::PBM(const String& fileName)
    : Image(), format(P1_ASCII), pixels(nullptr) {
    //load(fileName);
}

PBM::~PBM(){free();}
PBM::PBM(const PBM& other) : Image(other), format(other.format){
    copy(other);
}
PBM::PBM(PBM&& other) noexcept : Image(std::move(other)), format(other.format){
    move(std::move(other));
}
PBM& PBM::operator=(const PBM& other){
    if(this!=&other){
        free();
        copy(other);
        Image::operator=(other);
    }
    return *this;
}
PBM& PBM::operator=(PBM&& other) noexcept{
    if (this != &other){
        free();
        copy(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}
Image* PBM::collage(const Image* second, const String& newFileName, Direction direction) const{
    return second->collageWithPBM(this, newFileName, direction);
}
Image* PBM::collageWithPGM(const PGM* second, const String& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}
Image* PBM::collageWithPPM(const PPM* second, const String& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}

PBM* PBM::clone() const{return new PBM(*this);}
void PBM::free(){
    if (pixels != nullptr) {
        for (unsigned y = 0; y < height; ++y) {
            delete[] pixels[y];
        }
        delete[] pixels;
        pixels = nullptr;
    }
}
void PBM::move(PBM&& other){
    pixels = other.pixels;
    
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = std::move(other.magicNumber);
    fileName = std::move(other.fileName);
    
    format = other.format;
    other.pixels = nullptr;
    other.width = 0;
    other.height = 0;
    other.maxColourNumbers = 0;
    other.format = P1_ASCII;
    other.magicNumber = "";
    other.fileName = "";  
}
void PBM::copy(const PBM& other) {
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = other.magicNumber;
    fileName = other.fileName;
    format = other.format;
    pixels = other.pixels; 
} 
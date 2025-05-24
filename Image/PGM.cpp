#include "PGM.h"
#include "Image.h"
PGM::PGM() : Image(), format(P2_ASCII), pixels(nullptr) {}

PGM::PGM(const String& fileName)
    : Image(), format(P2_ASCII), pixels(nullptr) {
    //load(fileName);
}

PGM::~PGM(){free();}
PGM::PGM(const PGM& other) : Image(other), format(other.format){
    copy(other);
}
PGM::PGM(PGM&& other) noexcept : Image(std::move(other)), format(other.format){
    move(std::move(other));
}
PGM& PGM::operator=(const PGM& other){
    if(this!=&other){
        free();
        copy(other);
        Image::operator=(other);
    }
    return *this;
}
PGM& PGM::operator=(PGM&& other) noexcept{
    if (this != &other){
        free();
        copy(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}
Image* PGM::collage(const Image* second, const String& newFileName, Direction direction) const{
    return second->collageWithPGM(this, newFileName, direction);
}
Image* PGM::collageWithPBM(const PBM* second, const String& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}
Image* PGM::collageWithPPM(const PPM* second, const String& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}

PGM* PGM::clone() const{return new PGM(*this);}
void PGM::free(){
    if (pixels != nullptr) {
        for (unsigned y = 0; y < height; ++y) {
            delete[] pixels[y];
        }
        delete[] pixels;
        pixels = nullptr;
    }
}
void PGM::move(PGM&& other){
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
    other.format = P2_ASCII;
    other.magicNumber = "";
    other.fileName = "";  
}
void PGM::copy(const PGM& other) {
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = other.magicNumber;
    fileName = other.fileName;
    format = other.format;
    pixels = other.pixels; 
} 
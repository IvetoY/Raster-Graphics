#include "Image.h"
#include "../Utils/PathHelper.h"
Image::Image() : width(0), height(0), maxColourNumbers(0), magicNumber(new char[1]), fileName(new char[1]) {
    magicNumber[0] = '\0';
    fileName[0] = '\0';
}
Image::Image(unsigned _w, unsigned _h, uint8_t _m,const String& _mN, const String& _fN) : width(_w), height(_h), maxColourNumbers(_m), magicNumber(_mN), fileName(_fN) {}
unsigned Image::getHeight() const {return height;}
unsigned Image::getWidth() const {return width;}
const String& Image::getMagicNumber() const{return magicNumber;}
const String& Image::getFileName() const {return fileName;}

void Image::print(std::ostream& os) const{
    os<<fileName<<std::endl;
}
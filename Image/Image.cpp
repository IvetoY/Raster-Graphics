#include "Image.h"
#include "../Utils/PathHelper.h"
Image::Image() : width(0), height(0), maxColourNumbers(0), magicNumber(new char[1]), fileName(new char[1]) {
    magicNumber[0] = '\0';
    fileName[0] = '\0';
}

Image::Image(unsigned _w, unsigned _h, uint8_t _m,const String& _mN, const String& _fN, std::vector<std::vector<Pixel>> _p) : width(_w), height(_h), maxColourNumbers(_m), magicNumber(_mN), fileName(_fN), pixels(_p) {}
Image::Image(const Image& other) : width(other.width), height(other.height),maxColourNumbers(other.maxColourNumbers), magicNumber(other.magicNumber), fileName(other.fileName), pixels(other.pixels) {}
unsigned Image::getHeight() const {return height;}
unsigned Image::getWidth() const {return width;}
const String& Image::getMagicNumber() const{return magicNumber;}
const String& Image::getFileName() const {return fileName;}
void Image::setFileName(const String& name){
    if (name != "" && name != " ")
	{
		fileName= name;
		return;
	}

	throw std::invalid_argument("Name must not be empty or contain only spaces");
}

Pixel& Image::at(unsigned x, unsigned y) {
    if (x >= width || y >= height) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    return pixels[y][x];
}
const Pixel& Image::at(unsigned x, unsigned y) const {
    if (x >= width || y >= height) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    return pixels[y][x];
}
void Image::print(std::ostream& os) const{
    os<<fileName<<std::endl;
}




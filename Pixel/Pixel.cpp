#include "Pixel.h"

Pixel::Pixel() : red(0),green(0),blue(0) {}
Pixel::Pixel(uint8_t _r, uint8_t _g, uint8_t _b) : red(_r), green(_g), blue(_b) {}

uint8_t Pixel::getRed() const {return red;}
uint8_t Pixel::getGreen() const {return green;}
uint8_t Pixel::getBlue() const {return blue;}

void Pixel::setRed(uint8_t value){red = value;}
void Pixel::setGreen(uint8_t value){green = value;}
void Pixel::setBlue(uint8_t value){blue = value;}

void Pixel::setRGB(uint8_t _r, uint8_t _g, uint8_t _b){
    red = _r;
    green = _g;
    blue = _b;
}

bool Pixel::operator==(const Pixel& other) const{
    return red == other.red && green == other.green && blue == other.blue;
}

bool Pixel::operator!=(const Pixel& other) const{
    return red != other.red || green != other.green || blue != other.blue;
}

Pixel& Pixel::operator=(const Pixel& other){
    if (this != &other) {
        red = other.red;
        green = other.green;
        blue = other.blue;
    }
    return *this;
}

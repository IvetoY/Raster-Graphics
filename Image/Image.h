#pragma once
#include <cstdint>
#include <vector>
#include "../Pixel/Pixel.h"
#include "../String/String.h"
class Image{
    protected:
    unsigned width;
    unsigned height;
    uint8_t maxColourNumbers; // Maximum color value 0-255 for 8-bit RGB
    String magicNumber;
    String fileName;
    std::vector<std::vector<Pixel>> pixels;
    //Vector<?> awaitingTransformations;
    public:
    Image();
    Image(unsigned _w, unsigned _h, uint8_t _m, const  String& _mN,const String& _fN, std::vector<std::vector<Pixel>> _p); //add vector for transformations
    Image(const Image& other);
    virtual ~Image() = default;
    unsigned getWidth() const;
    unsigned getHeight() const;
    const String& getMagicNumber() const;
    const String& getFileName() const;

    void setFileName(const String& name);

    Pixel& at(unsigned x, unsigned y);
    const Pixel& at(unsigned x, unsigned y) const;

    void print(std::ostream& os) const;
    

};

class PPM;
class PGM;
class PBM;

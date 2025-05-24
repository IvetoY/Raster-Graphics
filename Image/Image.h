#pragma once
#include <cstdint>
#include <vector>
#include <memory>
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
    enum Direction{HORIZONTAL, VERTICAL};
    public:
    Image();
    Image(unsigned _w, unsigned _h, uint8_t _m, const  String& _mN,const String& _fN, std::vector<std::vector<Pixel>> _p); //add vector for transformations
    Image(const Image& other);
    virtual Image* clone() const = 0;
    virtual ~Image() = default;

    unsigned getWidth() const;
    unsigned getHeight() const;
    void setMaxColourValue(uint8_t value) {maxColourNumbers = value;}
    uint8_t getMaxColourNumbers() const {return maxColourNumbers;}
    const String& getMagicNumber() const;
    const String& getFileName() const;

    void setFileName(const String& name);

    Pixel& at(unsigned x, unsigned y);
    const Pixel& at(unsigned x, unsigned y) const;

    virtual void save(const String& path) const = 0;

    virtual Image* collage(const Image* second, const String& filename, Direction direction) const = 0;//to be done : type of images
    virtual Image* collageWithPPM(const PPM* ppm, const String& newFileName, Direction direction) const = 0;
    virtual Image* collageWithPBM(const PBM* pbm, const String& newFileName, Direction direction) const =0;
    virtual Image* collageWithPGM(const PGM* pgm, const String& newFilaName, Direction direction) const = 0;
    void print(std::ostream& os) const;
    //virtual void applyTransformation(const Transformation& transform) = 0;

    const String& getMagicNumber() const {return magicNumber;}


};

class PPM;
class PGM;
class PBM;

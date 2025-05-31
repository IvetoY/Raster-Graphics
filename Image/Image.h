#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "../Pixel/Pixel.h"
#include <cstring>
#include <string>
#include <utility>
#include "../Commands/Direction.h"
class PPM;
class PBM;
class PGM;

class Image{
    protected:
    unsigned width;
    unsigned height;
    uint8_t maxColourNumbers; // Maximum color value 0-255 for 8-bit RGB
    std::string magicNumber;
    std::string fileName;
    
    public:
    Image();
    Image(unsigned width, unsigned height, unsigned maxColorNumber,const std::string& magicNumber, const std::string& fileName);
    Image(const Image& other);
    Image(Image&& other) noexcept;
    Image(unsigned width, unsigned height);
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&) noexcept = default;

    void setWidth(unsigned value){width = value;}
    void setHeight(unsigned value){height = value;}

    virtual Image* clone() const = 0;
    virtual ~Image() = default;
    virtual void swap(Image& other) = 0;
    unsigned getWidth() const{return width;}
    unsigned getHeight() const{return height;}
    void setMaxColourValue(uint8_t value) {maxColourNumbers = value;}
    uint8_t getMaxColourNumbers() const {return maxColourNumbers;}
    virtual const std::string& getFileName() const = 0; 
    virtual const char* getFileExtension() const = 0;

    void setFileName(const std::string& name);

    virtual void saveASCII(const std::string& path) const = 0;
    virtual void loadASCII(const std::string& filePath) = 0;

    virtual void saveBinary(const std::string& path) const = 0;
    virtual void loadBinary(const std::string& filePath) = 0;

    virtual Image* collage(const Image* second, const std::string& filename, Direction direction) const = 0;
    virtual Image* collageWithPPM(const PPM* ppm, const std::string& newFileName, Direction direction) const = 0;
    virtual Image* collageWithPBM(const PBM* pbm, const std::string& newFileName, Direction direction) const =0;
    virtual Image* collageWithPGM(const PGM* pgm, const std::string& newFilaName, Direction direction) const = 0;
    void print(std::ostream& os) const;

    const std::string& getMagicNumber() const {return magicNumber;}

    virtual void grayscale() = 0;
	virtual void negative() = 0;
	virtual void monochrome() = 0;
    
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;

    virtual Pixel getPixel(unsigned x, unsigned y) const =0;

    virtual void setPixel(unsigned x, unsigned y, const Pixel& pixel)=0;
     
    //virtual Image* createNewImage(unsigned width, unsigned height) const = 0;
    //virtual void swap(Image& other) = 0;
};


#pragma once
#include "../Pixel/Pixel.h"
#include <vector>
#include "../Image/Image.h"

class PPM: public Image{
    enum Format{P3_ASCII, P6_BINARY};
private:
    Format format;
    void copy(const PPM& other);
    void move(PPM&& other);
    void free();
public:
    PPM();
    explicit PPM(String& fileName);
    PPM(unsigned _width, unsigned _height, uint8_t _maxColour, const String& _magicNum, const String& _fileName, const std::vector<std::vector<Pixel>>& _pixels, Format _format = P3_ASCII);
    
    PPM(const PPM& other);
    PPM(PPM&& other) noexcept;
    PPM& operator=(PPM&& other) noexcept;
    PPM& operator=(const PPM& other);
    ~PPM() ;

    Image* collage(const Image* second, const String& newFileName, Direction direction) const override;

    Image* collageWithPBM(const PBM* second, const String& newFileName, Direction direction) const;
    Image* collageWithPGM(const PGM* second, const String& newFileName, Direction direction) const;
    Image* collageWithPPM(const PPM* second, const String& newFileName, Direction direction) const;

    void save(const String& filename) const override;

    PPM* clone() const override;

    void setFormat(Format format) {this->format = format;}
    Format getFormat() const {return format;}

    const char* getFileExtension() const{return "ppm";}

};
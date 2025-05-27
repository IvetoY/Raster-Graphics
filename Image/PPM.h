#pragma once
#include "../Pixel/Pixel.h"
#include "Image.h"
#include <string>

class PPM: public Image{
    enum Format{P3_ASCII, P6_BINARY};
private:
    Format format;
    Pixel** pixels = nullptr;
    void copy(const PPM& other);
    void move(PPM&& other) noexcept;
    void free();
public:
    PPM();
    explicit PPM(const std::string& fileName);
    PPM(unsigned _width, unsigned _height, uint8_t _maxColourNumbers, 
         const std::string& _magicNumber, const std::string& _fileName,
         const Pixel* const* _pixels);
    PPM(unsigned width, unsigned height, uint8_t maxColourNumbers,
        const std::string& magicNumber, const std::string& fileName,
        Pixel**&& pixels, Format _format = P3_ASCII);

    PPM(const PPM& other);
    PPM(PPM&& other) noexcept;
    PPM& operator=(PPM&& other) noexcept;
    PPM& operator=(const PPM& other);
    ~PPM() ;

    Image* collage(const Image* second, const std::string& newFileName, Direction direction) const override;

    Image* collageWithPBM(const PBM* second, const std::string& newFileName, Direction direction) const;
    Image* collageWithPGM(const PGM* second, const std::string& newFileName, Direction direction) const;
    Image* collageWithPPM(const PPM* second, const std::string& newFileName, Direction direction) const;

    void save(const std::string& filename) const override;
    void load(const std::string& filename) override;

    void grayscale() override;
	void negative() override;
	void monochrome()override;
	void rotateLeft() override;
	void rotateRight() override;

    PPM* clone() const override;

    void setFormat(Format format) {this->format = format;}
    Format getFormat() const {return format;}

    const char* getFileExtension() const{return "ppm";}
    Pixel getPixel(unsigned x, unsigned y) const override;

    void setPixel(unsigned x, unsigned y, const Pixel& pixel) override;

};
#pragma once
#include "../Pixel/Pixel.h"
#include "Image.h"

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
    explicit PPM(const String& fileName);
    PPM(unsigned _width, unsigned _height, uint8_t _maxColourNumbers, 
         const String& _magicNumber, const String& _fileName,
         const Pixel* const* _pixels);
    PPM(unsigned width, unsigned height, uint8_t maxColourNumbers,
        const String& magicNumber, const String& fileName,
        Pixel**&& pixels, Format _format = P3_ASCII);

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
    void load(const String& filename) override;

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
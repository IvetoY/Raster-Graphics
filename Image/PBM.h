#pragma once 
#include "Image.h"
#include "../Pixel/Pixel.h"

class PBM: public Image{
    enum Format{P1_ASCII, P4_BINARY};
private:
    Format format;
    Pixel** pixels = nullptr;
    void copy(const PBM& other);
    void move(PBM&& other);
    void free();
public:

    PBM();
    explicit PBM(const String& fileName);
    PBM(unsigned _width, unsigned _height, uint8_t _maxColorNumber, const String& _magicNumber, const String& _fileName,const Pixel* const* _pixels);
    PBM(unsigned width, unsigned height, uint8_t maxColour,
        const String& magicNumber, const String& fileName,
        Pixel**&& pixels, Format _format = P1_ASCII);

    PBM(const PBM& other);
	PBM(PBM&& other) noexcept;
	PBM& operator=(const PBM& other);
	PBM& operator=(PBM&& other) noexcept;
	~PBM();

    Image* collage(const Image* second, const String& newFileName, Direction direction) const override;

	Image* collageWithPBM(const PBM* second, const String& newFileName, Direction direction) const;
    Image* collageWithPGM(const PGM* second, const String& newFileName, Direction direction) const;
    Image* collageWithPPM(const PPM* second, const String& newFileName, Direction direction) const;

    void save(const String& path)const override;
    void load(const String& filePath) override;

    void grayscale() override;
	void negative() override;
	void monochrome()override;
	void rotateLeft() override;
	void rotateRight() override;

	PBM* clone() const override;

    void setFormat(Format format) {this->format = format;}
    Format getFormat() const {return format;}

	const char* getFileExtension() const {return "pbm";}
    Pixel getPixel(unsigned x, unsigned y) const override;

    void setPixel(unsigned x, unsigned y, const Pixel& pixel) override;
};
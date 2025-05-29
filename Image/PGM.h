#pragma once 
#include "Image.h"
#include "../Pixel/Pixel.h"
#include <string>

class PGM: public Image{
    enum   Format{P2_ASCII, P5_BINARY};
    private:
    Format format;
    Pixel** pixels = nullptr;
    void copy(const PGM& other);
    void move(PGM&& other);
    void free();
public:

    void swap(Image& other) override;
    PGM();
    explicit PGM(const std::string& fileName);
    PGM(unsigned _width, unsigned _height, uint8_t _maxColorNumber, const std::string& _magicNumber, const std::string& _fileName,const Pixel* const* _pixels);
    PGM(unsigned width, unsigned height, uint8_t maxColorValue,
        const std::string& magicNumber, const std::string& fileName,
        Pixel**&& pixelsData, Format fmt = P2_ASCII);

    PGM(const PGM& other);
	PGM(PGM&& other) noexcept;
	PGM& operator=(const PGM& other);
	PGM& operator=(PGM&& other) noexcept;
	~PGM();

    Image* collage(const Image* second, const std::string& newFileName, Direction direction) const override;

	Image* collageWithPBM(const PBM* second, const std::string& newFileName, Direction direction) const ;
    Image* collageWithPGM(const PGM* second, const std::string& newFileName, Direction direction) const ;
    Image* collageWithPPM(const PPM* second, const std::string& newFileName, Direction direction) const;

    void saveASCII(const std::string& path)const override;
    void loadASCII(const std::string& filePath) override;

    void saveBinary(const std::string& path)const override;
    void loadBinary(const std::string& filePath) override;

    void grayscale() override;
	void negative() override;
	void monochrome()override;
	void rotateLeft() override;
	void rotateRight() override;

	PGM* clone() const override;

    void setFormat(Format format) {this->format = format;}
    Format getFormat() const {return format;}

	const char* getFileExtension() const {return "pgm";}
    Pixel getPixel(unsigned x, unsigned y) const override;

    const std::string& getFileName() const override {return fileName;}

    void setPixel(unsigned x, unsigned y, const Pixel& pixel) override;
};
#pragma once 
#include "Image.h"
#include "../Pixel/Pixel.h"

class PBM: public Image{
    enum Format{P1_ASCII, P4_BINARY};
private:
    Format format;
    uint8_t** pixels = nullptr;
    void copy(const PBM& other);
    void move(PBM&& other);
    void free();
public:

    PBM();
    explicit PBM(const String& fileName);
    PBM(unsigned _width, unsigned _height, uint8_t _maxColorNumber, const String& _magicNumber, const String& _fileName,std::vector<std::vector<Pixel>>& _pixels);
    PBM(unsigned _width, unsigned _height, uint8_t _maxColorNumber, const String& _magicNumber, const String& _fileName,uint8_t**&& pixels, Format format = P1_ASCII);

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

	PBM* clone() const override;

    void setFormat(Format format) {this->format = format;}
    Format getFormat() const {return format;}

	const char* getFileExtension() const {return "pbm";}
};
#pragma once 
#include "Image.h"
#include "../Pixel/Pixel.h"

class PGM: public Image{
    enum Format{P2_ASCII, P5_BINARY};
private:
    Format format;
    uint8_t** pixels = nullptr;
    void copy(const PGM& other);
    void move(PGM&& other);
    void free();
public:
    PGM();
    explicit PGM(const String& fileName);
    PGM(unsigned _width, unsigned _height, uint8_t _maxColorNumber, const String& _magicNumber, const String& _fileName,std::vector<std::vector<Pixel>>& _pixels);

    PGM(const PGM& other);
	PGM(PGM&& other) noexcept;
	PGM& operator=(const PGM& other);
	PGM& operator=(PGM&& other) noexcept;
	~PGM();

    Image* collage(const Image* second, const String& newFileName, Direction direction) const override;

	Image* collageWithPBM(const PBM* second, const String& newFileName, Direction direction) const ;
    Image* collageWithPGM(const PGM* second, const String& newFileName, Direction direction) const ;
    Image* collageWithPPM(const PPM* second, const String& newFileName, Direction direction) const;

    void save(const String& path)const override;

	PGM* clone() const override;

    void setFormat(Format format) {this->format = format;}
    Format getFormat() const {return format;}

	const char* getFileExtension() const {return "pgm";}
};
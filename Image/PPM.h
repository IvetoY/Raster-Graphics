#pragma once
#include "../Pixel/Pixel.h"
#include <vector>
#include "../Image/Image.h"

class PPM: public Image{
enum Format{P3_ASCII, P6_BINARY};
private:
Format format;
public:
    PPM();
    PPM(const PPM& other);
    explicit PPM(const String& fileName);
    ~PPM() override = default;
    PPM(unsigned _width, unsigned _height, uint8_t _maxColour, const String& _magicNum, const String& _fileName, const std::vector<std::vector<Pixel>>& _pixels, Format _format = P3_ASCII);
    PPM& PPM::operator=(PPM&& other) noexcept;
    PPM& PPM::operator=(const PPM& other);
    PPM(PPM&& other) noexcept;
    PPM(const PPM& other);

    void load(const String& filename) override;
    void save(const String& filename) const override;
    Image* collage(const Image* second, const String& newFileName) const override;

    Image* collageWithPBM(const PBM* second, const String& newFileName) const;
    Image* collageWithPGM(const PGM* second, const String& newFileName) const;
    Image* collageWithPPM(const PPM* second, const String& newFileName) const;

    PPM* clone() const override;

    void setFormat(Format format) {this->format = format;}
    Format getFormat() const {return format;}

    const String& getFileExtenension() const{return "ppm";}

    void copy(const PPM& other);
    void free();
    void move(PPM&& other);

};
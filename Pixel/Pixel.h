#pragma once
#include <cstdint>
class Pixel {
    uint8_t red, green, blue;
public:
    Pixel();
    Pixel(uint8_t _r, uint8_t _g, uint8_t _b);
    Pixel(const Pixel& other);
    
    uint8_t getRed() const;
    uint8_t getGreen() const;
    uint8_t getBlue() const;

    void setRed(uint8_t value);
    void setGreen(uint8_t value);
    void setBlue(uint8_t value);
    void setRGB(uint8_t red, uint8_t green, uint8_t blue);

    Pixel& operator=(const Pixel& other);
    bool operator==(const Pixel& other) const;
    bool operator!=(const Pixel& other) const;

    unsigned getGray() const;
    Pixel getRGB(const Pixel& other);
};
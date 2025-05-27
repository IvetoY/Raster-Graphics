#include "Monochrome.h"
#include "../Image/Image.h"
#include "../Pixel/Pixel.h"
#include "../System/System.h"
void Monochrome::apply(System& system) const {
    auto& images = system.getImages();
    
    for (auto& image : images) {
        for(unsigned y = 0; y < image.getHeight(); ++y) {
            for(unsigned x = 0; x < image.getWidth(); ++x) {
                Pixel pixel = image.getPixel(x,y);
                
                uint8_t brightness = static_cast<uint8_t>(0.299 * pixel.getRed() + 
                                                        0.587 * pixel.getGreen() + 
                                                        0.114 * pixel.getBlue());
                uint8_t value = (brightness > threshold) ? 255 : 0;
                pixel.setRGB(value, value, value);
                image.setPixel(x, y, pixel);
            }
        }
    }
}

Monochrome* Monochrome::clone() const{
    return new Monochrome(*this);
}
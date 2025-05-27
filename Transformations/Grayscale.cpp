#include "../Transformations/Transformations.h"
#include "../Image/Image.h"
#include "../Pixel/Pixel.h"
#include "Grayscale.h"
#include <cstring>
#include "../System/System.h"
void Grayscale::apply(System& system) const {
    auto& images = system.getImages();
    
    for (auto& image : images) {
        for(unsigned y = 0; y < image.getHeight(); ++y) {
            for(unsigned x = 0; x < image.getWidth(); ++x) {
                Pixel pixel = image.getPixel(x,y);
                uint8_t gray = static_cast<uint8_t>(0.299 * pixel.getRed() + 
                                                  0.587 * pixel.getGreen() + 
                                                  0.114 * pixel.getBlue());
                pixel.setRGB(gray, gray, gray);
                image.setPixel(x, y, pixel);
            }
        }
    }
}
Grayscale* Grayscale::clone() const{
    return new Grayscale(*this);
}

#include "Negative.h"
#include "../System/System.h"
void Negative::apply(System& system) const {
    auto& images = system.getImages();
    
    for (auto& image : images) {
        for(unsigned y = 0; y < image.getHeight(); ++y) {
            for(unsigned x = 0; x < image.getWidth(); ++x) {
                Pixel pixel = image.getPixel(x,y);
                pixel.setRGB(255 - pixel.getRed(),
                            255 - pixel.getGreen(),
                            255 - pixel.getBlue());
                image.setPixel(x, y, pixel);
            }
        }
    }
}
Negative* Negative::clone() const {
    return new Negative(*this);
}
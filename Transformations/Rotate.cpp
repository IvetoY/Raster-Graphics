#include "Rotate.h"
#include "../Image/PBM.h"
#include "../Image/PPM.h"
#include "../Image/PGM.h"
#include "../Image/ImageFactory.h"
#include <algorithm>
#include <stdexcept>
#include "../System/System.h"
Rotate::Rotate(Direction _d) : direction(_d) {
    if(_d!=left && _d!=right){
        throw std::invalid_argument("Invalid rotation direction. Use left or right");
    }
}
void Rotate::apply(System& system) const {
    auto& images = system.getImages();
    
    for (auto& image : images) {
        const unsigned width = image.getWidth();
        const unsigned height = image.getHeight();
        const unsigned newWidth = height;
        const unsigned newHeight = width;

        Image* rotated = image.clone();
        rotated->setHeight(newHeight);
        rotated->setWidth(newWidth);
        for (unsigned y = 0; y < height; ++y) {
            for (unsigned x = 0; x < width; ++x) {
                Pixel originalPixel = image.getPixel(x, y);
                
                if (direction == left) {
                    rotated->setPixel(height - 1 - y, x, originalPixel);
                } else { 
                    rotated->setPixel(y, width - 1 - x, originalPixel);
                }
            }
        }
        image.swap(*rotated);
        delete rotated;
    }
}

Rotate* Rotate::clone() const{
    return new Rotate(*this);
}

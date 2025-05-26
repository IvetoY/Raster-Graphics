#include "Rotate.h"
#include "../Image/PBM.h"
#include "../Image/PPM.h"
#include "../Image/PGM.h"
#include <algorithm>
#include <stdexcept>
Rotate::Rotate(Direction _d) : direction(_d) {
    if(_d!=left && _d!=right){
        throw std::invalid_argument("Invalid rotation direction. Use left or right");
    }
}

void Rotate::apply(Image& image) const {
    if (direction != left && direction != right) {
        throw std::runtime_error("Invalid rotation direction");
    }

    unsigned width = image.getWidth();
    unsigned height = image.getHeight();
    unsigned newWidth = height;
    unsigned newHeight = width;
    Image* rotated = image.createNewImage(newWidth, newHeight);
    
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

Rotate* Rotate::clone() const{
    return new Rotate(*this);
}

String Rotate::getTransformationName() const {
    return "Rotate transformation";
}
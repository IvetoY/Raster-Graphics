#include "../Transformations/Transformations.h"
#include "../Image/Image.h"
#include "../Pixel/Pixel.h"
#include "Grayscale.h"
void Grayscale::apply(Image& image) const {
    for(unsigned y = 0;y<image.getHeight(); ++y){
        for(unsigned x = 0; x<image.getWidth(); ++x){
            Pixel pixel = image.getPixel(x,y);
            uint8_t gray = static_cast<uint8_t>(0.299 * pixel.getRed() + 0.587 * pixel.getGreen() + 0.114 * pixel.getBlue());
            pixel.setRGB(gray, gray, gray);
        }
    }
}
Grayscale* Grayscale::clone() const{
    return new Grayscale(*this);
}
String Grayscale::getTransformationName() const {return "Grayscale transformation";}
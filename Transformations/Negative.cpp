#include "Negative.h"
void Negative::apply(Image& image) const {
    for(unsigned y = 0; y< image.getHeight(); ++y){
        for(unsigned x = 0;x<image.getWidth(); ++x){
            Pixel& pixel = image.at(x,y);
            pixel.setRGB(255-pixel.getRed(), 255-pixel.getGreen(), 255  - pixel.getBlue());
        }
    }
}
String Negative::getTransformationName() const {
    return "Negative transformation";
}
Negative* Negative::clone() const {
    return new Negative(*this);
}
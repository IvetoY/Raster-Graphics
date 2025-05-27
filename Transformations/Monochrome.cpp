#include "Monochrome.h"
#include "../Image/Image.h"
#include "../Pixel/Pixel.h"
void Monochrome::apply(Image& image) const {
for(unsigned y =0; y< image.getHeight();++y){
    for(unsigned x=0;x<image.getWidth();++x){
        Pixel pixel = image.getPixel(x,y);

        uint8_t brightness = static_cast<uint8_t>(0.299 * pixel.getRed() + 0.587 * pixel.getGreen() + 0.114 * pixel.getBlue());
        uint8_t value;
        if(brightness>threshold){value = 255;}
        else {value = 0;}
        pixel.setRGB(value, value, value);
    }

}
}

Monochrome* Monochrome::clone() const{
    return new Monochrome(*this);
}
#include "Rotate.h"
#include <algorithm>
#include <stdexcept>
Rotate::Rotate(Direction _d) : direction(_d) {
    if(_d!=left && _d!=right){
        throw std::invalid_argument("Invalid rotation direction. Use left or right");
    }
}

void Rotate::apply(Image& image) const {
    if(direction!=left && direction!=right){
        throw std::runtime_error("Corrupted rotation direction");
    }

    std::vector<std::vector<Pixel>> rotatedImage;
    unsigned newWidth = image.getHeight();
    unsigned newHeight = image.getWidth();

    rotatedImage.resize(newHeight, std::vector<Pixel>(newWidth)); 

    for(unsigned y = 0; y<image.getHeight(); ++y){
        for(unsigned x = 0;x<image.getWidth(); ++x){
            switch (direction)
            {
            case left:
                rotatedImage[newWidth-1-x][y] = image.at(x,y);
                break;
                case right:
                rotatedImage[x][newHeight-1-y] = image.at(x,y);
                break;
            }
        }
    }
    //otdelno za trite vida trqbva da se napravi
    //image = PPM(newWidth, newHeight, image.getMaxColorNumbers(), image.getMagicNumber(), image.getFileName(), rotatedImage );

}

Rotate* Rotate::clone() const{
    return new Rotate(*this);
}

String Rotate::getTransformationName() const {
    return "Rotate transformation";
}
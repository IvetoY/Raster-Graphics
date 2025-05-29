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
        if(direction==left){
            image.rotateLeft();
        }
        else{
            image.rotateRight();
        }
        
        
    }
}

Rotate* Rotate::clone() const{
    return new Rotate(*this);
}

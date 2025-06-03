#include "Collage.h"
#include "../Image/PBM.h"
#include "../Image/PGM.h"
#include "../Image/PPM.h"
#include <algorithm>
Collage::Collage(Image* s, Direction d, std::string fP) : 
                second(s), direction(d), filePath(fP) {}
Collage::~Collage(){
    freeResources();
}

void Collage::freeResources() {
   
    delete second;
    second = nullptr;
}

void Collage::apply(System& system) const {
        Session* session = system.getCurrentSession();
        if (!session) throw std::runtime_error("No active session");
        
        std::vector<Image*> images = session->getImages();
        if (images.empty()) throw std::runtime_error("No images in session");
        
        Image* first = images.back();
        
        if (!second) throw std::runtime_error("Second image not loaded");
        if (first->getFileExtension() != second->getFileExtension()) {
            throw std::runtime_error("Cannot create collage - different image types");
        }
        
        Image* result = first->collage(second, filePath, direction);
        if (!result) throw std::runtime_error("Collage creation failed");
        
        try {
            if(result->getMagicNumber() == "P1" || result->getMagicNumber() == "P2" || result->getMagicNumber() == "P3") {
                result->saveASCII(filePath);
            } else {
                result->saveBinary(filePath);
            }
            
        } catch (...) {
            delete result;
            throw;
        }
    }

Transformations* Collage::clone() const {
    return new Collage(second->clone(), direction, filePath);
}
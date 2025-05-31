#include "Collage.h"
#include "../Image/PBM.h"
#include "../Image/PGM.h"
#include "../Image/PPM.h"
#include <algorithm>
Collage::Collage(Image* f, Image* s, Direction d, std::string fP) : 
                first(f), second(s), direction(d), filePath(fP) {}
Collage::~Collage(){
    freeResources();
}

void Collage::freeResources() {
    delete first;
    delete second;
    first = nullptr;
    second = nullptr;
}
void Collage::apply(System& system) const {
    if (!first || !second) {
        throw std::runtime_error("One or both images are not loaded");
    }

    if (first->getFileExtension() != second->getFileExtension()) {
        throw std::runtime_error("Cannot create collage - images are of different types");
    }
    if (direction == Direction::HORIZONTAL) {
        if (first->getHeight() != second->getHeight()) {
            throw std::runtime_error("For horizontal collage, images must have the same height");
        }
    } else { 
        if (first->getWidth() != second->getWidth()) {
            throw std::runtime_error("For vertical collage, images must have the same width");
        }
    }
    Image* result = nullptr;
    try {
        if (auto ppm1 = dynamic_cast<PPM*>(first)) {
            auto ppm2 = dynamic_cast<PPM*>(second);
            if (!ppm2) throw std::runtime_error("Both images must be of the same type");
            
            if (direction == Direction::HORIZONTAL) {
                result = ppm1->collage(ppm2 , filePath, Direction::HORIZONTAL);
            } else {
                result = ppm1->collage(ppm2, filePath, Direction::VERTICAL);
            }
        }
        else if (auto pgm1 = dynamic_cast<PGM*>(first)) {
            auto pgm2 = dynamic_cast<PGM*>(second);
            if (!pgm2) throw std::runtime_error("Both images must be of the same type");
            
            if (direction == Direction::HORIZONTAL) {
                result = pgm1->collage(pgm2,filePath, Direction::HORIZONTAL);
            } else {
                result = pgm1->collage(pgm2, filePath, Direction::VERTICAL);
            }
        }
        else if (auto pbm1 = dynamic_cast<PBM*>(first)) {
            auto pbm2 = dynamic_cast<PBM*>(second);
            if (!pbm2) throw std::runtime_error("Both images must be of the same type");
            
            if (direction == Direction::HORIZONTAL) {
                result = pbm1->collage(pbm2,filePath, Direction::HORIZONTAL);
            } else {
                result = pbm1->collage(pbm2,filePath, Direction::VERTICAL);
            }
        }
        else {
            throw std::runtime_error("Unsupported image type for collage");
        }
        if (result && !filePath.empty()) {
            if(result->getMagicNumber() == "P1" || result->getMagicNumber() == "P2" || result->getMagicNumber() == "P3"){
                result->saveASCII(filePath);
            }
            else {
                result->saveBinary(filePath);
            }
            
            delete result;
        }
}
catch (...) {
        if (result) delete result;
        throw;
    }
}

Commands* Collage::clone() const {
    return new Collage(first->clone(), second->clone(), direction, filePath);
}
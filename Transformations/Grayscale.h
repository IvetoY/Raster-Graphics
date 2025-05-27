#pragma once 
#include "Transformations.h"
#include <cstring>

class Grayscale: public Transformations{
public:
    void apply(Image& image) const override;
    Grayscale* clone() const override;
    
};
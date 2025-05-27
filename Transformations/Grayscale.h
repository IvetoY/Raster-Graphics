#pragma once 
#include "Transformations.h"
#include <cstring>

class Grayscale: public Transformations{
public:
    void apply(System& system) const override;
    Grayscale* clone() const override;
    
};
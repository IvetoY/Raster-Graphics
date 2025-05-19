#pragma once 
#include "Transformations.h"

class Grayscale: public Transformations{
public:
    void apply(Image& image) const override;
    Grayscale* clone() const override;
    String getTransformationName() const override;
};
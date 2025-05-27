#pragma once 
#include "Transformations.h"
class Monochrome: public Transformations{
    private:
    uint8_t threshold = 128;
    public:
    void apply(Image& image) const override;
    Monochrome* clone() const override;
};
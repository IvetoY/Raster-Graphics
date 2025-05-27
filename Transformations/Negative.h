#pragma once 
#include "Transformations.h"

class Negative: public Transformations{
public:
void apply(Image& image) const override;
Negative* clone() const override;
};
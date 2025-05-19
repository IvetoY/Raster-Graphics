#pragma once
#include "../Image/Image.h"
class Transformations{
    public:
    virtual ~Transformations() = default;
    virtual void apply(Image& img) const = 0;
    virtual Transformations* clone() const = 0;
    virtual String getTransformationName() const = 0;
};
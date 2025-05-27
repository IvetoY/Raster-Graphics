#pragma once
#include "../Image/Image.h"
class System;
class Transformations{
    public:
    virtual ~Transformations() = default;
    virtual void apply(System& img) const = 0;
    virtual Transformations* clone() const = 0;
};
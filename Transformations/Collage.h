#pragma once
#include "Transformations.h"
#include "../System/System.h"
#include "../Commands/Direction.h"
#include "../Image/Image.h"
class Collage: public Transformations{

private:
Image* second;
Direction direction;
std::string filePath;
void freeResources();
public:
    ~Collage () override;
    Collage(Image* s, Direction d, std::string filePath);
    void apply(System& system) const override;
    Transformations* clone() const override;
};
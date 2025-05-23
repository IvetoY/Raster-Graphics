#pragma once
#include "Transformations.h"
#include <stdexcept>
class Rotate: public Transformations{
public:
enum Direction{left, right};
explicit Rotate(Direction d);
void apply(Image& image) const override;
Rotate* clone() const override;
String getTransformationName() const override;

Direction direction;
};
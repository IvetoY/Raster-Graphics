#pragma once
#include "Transformations.h"
#include <stdexcept>
class Rotate: public Transformations{
public:
enum Direction{left, right};
explicit Rotate(Direction d);
void apply(System& image) const override;
Rotate* clone() const override;

Direction direction;
};
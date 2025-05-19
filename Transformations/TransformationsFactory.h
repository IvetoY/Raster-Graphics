#pragma once
#include <memory>
#include "Transformations.h"
#include "../String/String.h"
#include "Grayscale.h"
#include "Monochrome.h"
#include "Rotate.h"
#include "Negative.h"
#include <stdexcept>

class TransformationsFactory{
public:
static std::unique_ptr<Transformations> create(const String& name){
    if(name == "grayscale") {return std::make_unique<Grayscale>();}
    if(name == "monochrome") {return std::make_unique<Monochrome>();}
    if(name == "rotate_left") {return std::make_unique<Rotate>(Rotate::left);}
    if(name == "rotate_right") {return std::make_unique<Rotate>(Rotate::right);}
    if(name == "negative") {return std::make_unique<Negative>();}
    throw std::invalid_argument(std::string("Unknown transformation: ") + name.c_str());
}
};
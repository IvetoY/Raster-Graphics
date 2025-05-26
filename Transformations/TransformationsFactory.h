#pragma once
#include "Transformations.h"
#include "../Structures/String/String.h"
#include "Grayscale.h"
#include "Monochrome.h"
#include "Rotate.h"
#include "Negative.h"
#include <stdexcept>

class TransformationsFactory{
public:
static Transformations* create(const String& name){
    if(name == "grayscale") {return new Grayscale();}
    if(name == "monochrome") {return new Monochrome();}
    if(name == "rotate_left") {return new Rotate(Rotate::left);}
    if(name == "rotate_right") {return new Rotate(Rotate::right);}
    if(name == "negative") {return new Negative();}
    throw std::invalid_argument(std::string("Unknown transformation: ") + name.c_str());
}
static void destroy(Transformations* tr) {delete tr;}
};
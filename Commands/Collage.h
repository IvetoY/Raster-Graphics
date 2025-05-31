#pragma once
#include "Commands.h"
#include "../System/System.h"
#include "Direction.h"
class Collage: public Commands{

private:
Image* first;
Image* second;
Direction direction;
std::string filePath;
void freeResources();
public:
    ~Collage () override;
    Collage(Image* f, Image* s, Direction d, std::string filePath);
    void apply(System& system) const override;
    Commands* clone() const override;
    String getCommandName() const override {return "collage";}
    String getCommandDescription() const override {return "";}
};
#pragma once
#include "Commands.h"
#include "../System/System.h"
class Collage: public Commands{
public:
    void apply(System& system) const override;
    Commands* clone() const override;
    String getCommandName() const override {return "collage";}
    String getCommandDescription() const override {return "";}
};
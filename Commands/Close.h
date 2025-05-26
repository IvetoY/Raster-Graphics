#pragma once
#include "Commands.h"
#include "../System/System.h"
class Close: public Commands{
public:
    void apply(System& system) const override;
    Commands* clone() const override;
    String getCommandName() const override {return "close";}
    String getCommandDescription() const override {return "Closes the current image";}
};
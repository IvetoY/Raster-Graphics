#pragma once
#include "Commands.h"
#include "../System/System.h"
class Close: public Commands{
public:
    void apply(System& system) const override;
    Commands* clone() const override;
    std::string getCommandName() const override {return "close";}
    std::string getCommandDescription() const override {return "Closes the current image";}
};
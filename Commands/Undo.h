#pragma once
#include "Commands.h"
#include "../System/System.h"

class Undo: public Commands{
public:
    void apply(System& system) const override;
    Commands* clone() const override;
    Undo() = default;
    std::string getCommandName() const override {return "undo";}
    std::string getCommandDescription() const override {return "Undoes the last command";}
};
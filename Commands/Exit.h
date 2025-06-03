#pragma once
#include "Commands.h"
#include "../System/System.h"
class Exit : public Commands{
public:
    void apply(System& system) const  override;
    Commands* clone() const override;
    std::string getCommandName() const override {return "exit";}
    std::string getCommandDescription() const override {return "Exits the program";}
};
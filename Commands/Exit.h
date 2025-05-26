#pragma once
#include "Commands.h"
#include "../System/System.h"
class Exit : public Commands{
public:
    void apply(System& system) const  override;
    Commands* clone() const override;
    String getCommandName() const override {return "exit";}
    String getCommandDescription() const override {return "Exits the program";}
};
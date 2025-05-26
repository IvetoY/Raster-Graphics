#pragma once
#include "Commands.h"

class Help : public Commands{
public:
    Help() = default;
    void apply(System& system)const override;
    Commands* clone() const override;
    String getCommandName() const override {return "help";}
    String getCommandDescription() const override {return "Displays help information";}
};
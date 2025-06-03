#pragma once
#include "Commands.h"
#include "../System/System.h"
class Help : public Commands{
public:
    Help() = default;
    void apply(System& system)const override;
    Commands* clone() const override;
    std::string getCommandName() const override {return "help";}
    std::string getCommandDescription() const override {return "Displays help information";}
};
#pragma once
#include "Commands.h"
#include "../System/System.h"
class Switch : public Commands {
    int switchTo;
public:
    explicit Switch(int switchTo);
    explicit Switch(const std::string& idStr);
    void apply(System& system) const override;
    Commands* clone() const override;
    String getCommandName() const override {return "switch";}
    String getCommandDescription() const override {return "Switches active image";}
};
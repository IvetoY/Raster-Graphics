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
    std::string getCommandName() const override {return "switch";}
    std::string getCommandDescription() const override {return "";}
};
#pragma once
#include "Commands.h"

class Exit : public Commands{
public:
    void apply(Session& session) override;
    void undo(Session& session) override {}
    String getCommandName() const override {return "exit";}
    String getCommandDescription() const override {return "Exits the program";}
};
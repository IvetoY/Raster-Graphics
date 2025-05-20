#pragma once
#include "Commands.h"

class Help : public Commands{
public:
    void apply(Session& session) override;
    void undo(Session& session) override{}
    String getCommandName() const override {return "help";}
    String getCommandDescription() const override {return "Displays help information";}
};
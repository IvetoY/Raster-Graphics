#pragma once
#include "Commands.h"

class Undo: public Commands{
public:
    void apply(Session& session) override;
    void undo(Session& session) override {}
    String getCommandName() const override {return "undo";}
    String getCommandDescription() const override {return "Undoes the last command";}
};
#pragma once
#include "Commands.h"

class Close: public Commands{
public:
    void apply(Session& session) override;
    void undo(Session& session) override;
    String getCommandName() const override {return "close";}
    String getCommandDescription() const override {return "Closes the current image";}
};
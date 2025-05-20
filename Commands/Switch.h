#pragma once
#include "Commands.h"
#include "../String/String.h"
class Switch : public Commands {
    size_t newIndex;
    size_t previousIndex;
public:
    explicit Switch(size_t index) : newIndex(index) {}
    
    void apply(Session& session) override;
    void undo(Session& session) override;
    String getCommandName() const override {return "switch";}
    String getCommandDescription() const override {return "Switches active image";}
};
#pragma once
#include "Commands.h"

class SessionInfo : public Commands{
public:
    void apply(System& system) const override;
    Commands* clone() const override;
    SessionInfo() = default;
    String getCommandName() const override {return "sessioninfo";}
    String getCommandDescription() const override {return "Displays session information";}
};
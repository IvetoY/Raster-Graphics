#pragma once
#include "Commands.h"
#include "../System/System.h"
class SessionInfo : public Commands{
public:
    void apply(System& system) const override;
    Commands* clone() const override;
    SessionInfo() = default;
    std::string getCommandName() const override {return "sessioninfo";}
    std::string getCommandDescription() const override {return "Displays session information";}
};
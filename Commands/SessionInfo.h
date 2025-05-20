#pragma once
#include "Commands.h"

class SessionInfo : public Commands{
public:
    void apply(Session& session) override;
    void undo(Session& session) override {}
    String getCommandName() const override {return "sessioninfo";}
    String getCommandDescription() const override {return "Displays session information";}
};
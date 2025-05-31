#pragma once
#include "Commands.h"
#include "../System/System.h"
class SaveAs: public Commands{
    private:
    std::string newFileName;
public:
    SaveAs(const std::string& _newFileName);
    void apply(System& system) const override;
    Commands* clone() const override;
    String getCommandName() const override {return "saveas";}
    String getCommandDescription() const override {return "";}
};
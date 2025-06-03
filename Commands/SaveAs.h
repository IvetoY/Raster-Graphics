#pragma once
#include "Commands.h"
#include "../System/System.h"
#include <string>
class SaveAs: public Commands{
private:
    std::string newFileName;
public:
    SaveAs(const std::string& _newFileName);
    void apply(System& system) const override;
    Commands* clone() const override;
    std::string getCommandName() const override {return "saveas";}
    std::string getCommandDescription() const override {return "";}
};
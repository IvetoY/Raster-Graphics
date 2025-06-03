#pragma once
#include "Commands.h"
#include "../System/System.h"
#include <string>
class Save: public Commands{
    private:
    std::string filename;
    public:
    Save();
    Commands* clone() const override;
    void apply(System& system)const override;
    std::string getCommandName() const override {return "save";}
    std::string getCommandDescription() const override {return "Saves image to file";}
};
#pragma once
#include "Commands.h"
#include "../System/System.h"
#include "../Structures/String/String.h"
class Save: public Commands{
    private:
    String filename;
    public:
    Save()=default;
    Save(const String& filename);
    Commands* clone() const override;
    void apply(System& system)const override;
    String getCommandName() const override {return "save";}
    String getCommandDescription() const override {return "Saves image to file";}
};
#pragma once
#include "../Commands/Commands.h"
#include "../Structures/String/String.h"
#include "../System/System.h"
class Add: public Commands{
    private:
    String filename;
public:
    Add(const String& filename);
    Add(String&& filename);
    void apply(System& system) const override;
    Commands* clone() const override;
    String getCommandName() const override {return "add";}
    String getCommandDescription() const override {return "Adds a new image to session";}
    
};
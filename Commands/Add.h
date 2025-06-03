#pragma once
#include "../Commands/Commands.h"
#include "../System/System.h"
#include <string>
class Add: public Commands{
private:
    std::string filename;
public:
    Add(const std::string& filename);
    Add(std::string&& filename);
    void apply(System& system) const override;
    Commands* clone() const override;
    std::string getCommandName() const override {return "add";}
    std::string getCommandDescription() const override {return "Adds a new image to session";}
    
};
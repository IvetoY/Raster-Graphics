#pragma once
#include "Commands.h"
#include "../System/System.h"
#include <string>
#include <vector>
class Load: public Commands{
    private:
    std::vector<std::string> files;
    public:
    ~Load() override = default;
    Load(const std::vector<std::string>& files);
    Commands* clone() const override;
    void apply(System& system) const override;
    std::string getCommandName() const override{return "load";}
    std::string getCommandDescription() const override {return "Loads an image from file";}
};
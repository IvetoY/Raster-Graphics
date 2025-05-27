#pragma once
#include "../Structures/String/String.h"
#include <vector>
#include "Commands.h"
#include "../System/System.h"
#include <string>
class Load: public Commands{
    private:
    std::string file;
    public:
    ~Load() override = default;
    Load(const std::string& files);
	Load(std::string&& files);
    Commands* clone() const override;
    void apply(System& system) const override;
    String getCommandName() const override{return "load";}
    String getCommandDescription() const override {return "Loads an image from file";}
};
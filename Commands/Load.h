#pragma once
#include "../Structures/String/String.h"
#include <vector>
#include "Commands.h"
#include "../System/System.h"
class Load: public Commands{
    private:
    std::vector<String> files;
    public:
    ~Load() override = default;
    Load(const std::vector<String>& files);
	Load(std::vector<String>&& files);
    Commands* clone() const override;
    void apply(System& system) const override;
    String getCommandName() const override{return "load";}
    String getCommandDescription() const override {return "Loads an image from file";}
};
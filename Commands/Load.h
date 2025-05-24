#pragma once
#include "../Transformations/Transformations.h"
#include "Commands.h"
class Load: public Commands{
    String filePath;
    int sessionID;
    public:
    Load() {}
    Load(String& _filePath) : filePath(_filePath){}
    void apply(Session& session) override;
    void undo(Session& session) override;
    String getCommandName() const override{return "load";}
    String getCommandDescription() const override {return "Loads an image from file";}
};
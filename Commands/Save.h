#pragma once
#include "Commands.h"
#include "../String/String.h"

class Save: public Commands{
    String filePath;
    size_t imageId;
    public:
    Save(const String& _path, size_t _id);

    void apply(Session& session) override;
    void undo(Session& session) override{}
    String getCommandName() const override {return "save";}
    String getCommandDescription() const override {return "Saves image to file";}
};
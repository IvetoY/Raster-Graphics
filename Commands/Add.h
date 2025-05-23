#pragma once
#include "Commands.h"
#include <memory>
#include "../Image/Image.h"
class Add: public Commands{
    Image* image;
public:
    explicit Add(Image* img);
    Add(const Add&) = delete;
    Add& operator=(const Add&) = delete;
    void apply(Session& session) override;
    void undo(Session& session) override;
    String getCommandName() const override {return "add";}
    String getCommandDescription() const override {return "Adds a new image to session";}
    ~Add() override{
        delete image;
    }
};
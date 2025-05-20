#pragma once
#include "Commands.h"
#include <memory>
#include "../Image/Image.h"
class Add: public Commands{
    std::unique_ptr<Image> image;
public:
    explicit Add(std::unique_ptr<Image> img) : image(std::move(img)) {}
    
    void apply(Session& session) override;
    void undo(Session& session) override;
    String getCommandName() const override {return "add";}
    String getCommandDescription() const override {return "Adds a new image to session";}
};
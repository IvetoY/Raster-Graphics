#pragma once
#include "Image.h"
#include <memory>

class ImageFactory{
public:
static std::unique_ptr<Image> create(String path) {
    return std::make_unique<Image>(path);
}
};
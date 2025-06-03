#include "Session.h"
#include <stdexcept>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <iostream>
int Session::nextId = 1;

Session::Session() : id(nextId++), active(true) {}

Session::~Session() {
    clearImages();
    clearTransformations();
    clearHistory();
}
void Session::clearImages() {
    for (Image* img : images) {
        delete img;
    }
    images.clear();
}

void Session::clearTransformations() {
    for (auto& transformation : pendingTransformations) {
        delete transformation;
    }
    pendingTransformations.clear();
}

void Session::clearHistory() {
    for (auto& entry : history) {
        for (Image* img : entry) delete img;
    }
    history.clear();
    
    for (auto& entry : transformationsHistory) {
        for (Transformations* trans : entry) delete trans;
    }
    transformationsHistory.clear();
}
void Session::addImage(Image* image) {
    if (!image){throw std::invalid_argument("Image pointer is null");}
    saveState();
    images.push_back(image);
}
std::vector<Image*> Session::cloneImages(const std::vector<Image*>& source) {
        std::vector<Image*> copies;
        for (const auto& img : source) {
        copies.push_back(img ? img->clone() : nullptr);
    }
        return copies;
    }

void Session::saveState() {
    history.push_back(cloneImages(images));
    transformationsHistory.push_back(cloneTransformations(pendingTransformations));
}
std::vector<Transformations*> Session::cloneTransformations(
    const std::vector<Transformations*>& source) {
    std::vector<Transformations*> copies;
    for (const auto& trans : source) {
        copies.push_back(trans ? trans->clone() : nullptr);
    }
    return copies;
}
void Session::loadImage(const std::string& filename) {
    Image* newImage = ImageFactory::create(filename);
    try {
        addImage(newImage);
    } catch (...){
        delete newImage;
        throw;
    }
}

void Session::closeImage() {
    if (images.empty()) {
        throw std::runtime_error("No images to close");
    }
    
    history.push_back(cloneImages(images));
    
    delete images.back();
    images.pop_back();
}

std::vector<Image*> Session::getImages() const {
    return images;
}
void Session::queueTransformation(Transformations* transformation) {
    if (!transformation) {throw std::invalid_argument("Transformation pointer is null");}
     saveState();

     pendingTransformations.push_back(transformation);
}

void Session::applyTransformations(System& system) {
    if (pendingTransformations.empty()) return;
    saveState();
    for (auto& transformation : pendingTransformations) {
        if (transformation) {
            transformation->apply(system);
        }
    }
    pendingTransformations.clear();
}
bool Session::hasPendingTransformations() const {
    return !pendingTransformations.empty();
}
void Session::undo() {
    if (history.empty()) {
        throw std::runtime_error("Nothing to undo");
    }
    clearImages();
    clearTransformations();
    images = history.back();
    history.pop_back();

    pendingTransformations = transformationsHistory.back();
    transformationsHistory.pop_back();
}

void Session::save(const std::string& filename) const {
    if(images.empty()){throw std::runtime_error("No images to save");}
    
    for (Image* img : images) {
        std::cout << "DEBUG: Saving image: " << img->getFileName() << std::endl; //
        const std::string& magic = img->getMagicNumber();
        if (magic == "P1" || magic == "P2" || magic == "P3") {
            img->saveASCII(img->getFileName());
        } else {
            img->saveBinary(img->getFileName());
        }
    }

}

void Session::saveFirstFileAs(const std::string& newFileName) const {
    if (images.empty()) {
        throw std::runtime_error("No images in session");
    }
    
    Image* firstImage = images.front();
    const std::string& magic = firstImage->getMagicNumber();
    if (magic == "P1" || magic == "P2" || magic == "P3") {
        firstImage->saveASCII(newFileName);
    } else {
        firstImage->saveBinary(newFileName);
    }
}

void Session::terminate() {
    if (active) {
        active = false;
        clearImages();
        clearTransformations();
        clearHistory();
    }
}
void Session::printSessionInfo(std::ostream& out) const {
    out << "Session ID: " << id << "\n"
        << "Status: " << (active ? "Active" : "Inactive") << "\n"
        << "Images count: " << images.size() << "\n"
        << "Pending transformations: " << pendingTransformations.size() << "\n"
        << "History states: " << history.size() << "\n";
}

void Session::resetSessionCounter() {
    nextId = 1;
}
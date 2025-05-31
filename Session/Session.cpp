#include "Session.h"
#include <stdexcept>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
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

void Session::clearTransformations(){
    for (Transformations* trans : transformations) {
        delete trans;
    }
    transformations.clear();
}

void Session::clearHistory(){
   for (auto& historyEntry : history) {
        for (Image* img : historyEntry) {
            delete img;
        }
    }
    history.clear();
}
void Session::addImage(Image* image) {
    if (!image){throw std::invalid_argument("Image pointer is null");}
    history.push_back(cloneImages(images));
    images.push_back(image);
}
std::vector<Image*> Session::cloneImages(const std::vector<Image*>& source) {
        std::vector<Image*> copies;
        for (Image* img : source) {
            copies.push_back(img->clone());
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
    transformations.push_back(transformation);
}

void Session::undo() {
    if (history.empty()) {throw std::runtime_error("Nothing to undo");}
    
    clearImages();
    
    images = cloneImages(history.back());
    for (Image* img : history.back()) {
        delete img;
    }
    history.pop_back();
}

void Session::save(const std::string& filename) const {
    if(images.empty()){throw std::runtime_error("No images to save");}
    
    for (Image* img : images) {
        std::cout << "DEBUG: Saving image: " << img->getFileName() << std::endl;
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
        << "Pending transformations: " << transformations.size() << "\n";
}

void Session::resetSessionCounter() {
    nextId = 1;
}
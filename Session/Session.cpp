#include "Session.h"
#include <stdexcept>
#include <fstream>
#include <stack>
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
    while (!images.empty()) {
        delete images.top();
        images.pop();
    }
}

void Session::clearTransformations(){
    while (!transformations.empty()) {
        delete transformations.top();
        transformations.pop();
    }
}

void Session::clearHistory(){
    while (!history.empty()) {
        delete history.top();
        history.pop();
    }
}
void Session::addImage(Image* image) {
    if (!image){throw std::invalid_argument("Image pointer is null");}

    if (!images.empty()){
        history.push(images.top()->clone());
    }
    
    images.push(image);
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
    if (images.empty()) {throw std::runtime_error("No images to close");}
    
    if (images.size() > 1) {
        Image* temp = images.top();
        images.pop();
        history.push(images.top()->clone());
        images.push(temp);
    }

    delete images.top();
    images.pop();
}

std::vector<Image*> Session::getImages() const {
    std::vector<Image*> result;
    std::stack<Image*> temp = images;
    
    while (!temp.empty()) {
        if (temp.top() != nullptr) {
            result.push_back(temp.top());
        }
        temp.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}
void Session::queueTransformation(Transformations* transformation) {
    if (!transformation) {throw std::invalid_argument("Transformation pointer is null");}
    transformations.push(transformation);
}

void Session::undo() {
    if (history.empty()) {throw std::runtime_error("Nothing to undo");}
    
    if(!images.empty()){
        delete images.top();
        images.pop();
    }
    images.push(history.top());
    history.pop();
}

void Session::save(const std::string& filename) const {
    if(images.empty()){throw std::runtime_error("No images to save");}
    
    const std::string& magic = images.top()->getMagicNumber();
    if (magic == "P1" || magic == "P2" || magic == "P3") {
        images.top()->saveASCII(filename);
    } else {
        images.top()->saveBinary(filename);
    }
}

void Session::saveFirstFileAs(const std::string& newFileName) const {
    if (images.empty()) {
        throw std::runtime_error("No images in session");
    }
    
    
    std::stack<Image*> temp = images;
    std::stack<Image*> reversed;
    while (!temp.empty()) {
        reversed.push(temp.top());
        temp.pop();
    }
    
    if (!reversed.empty()) {
        Image* firstImage = reversed.top();
        const std::string& magic = firstImage->getMagicNumber();
        if (magic == "P1" || magic == "P2" || magic == "P3") {
            firstImage->saveASCII(newFileName);
        } else {
            firstImage->saveBinary(newFileName);
        }
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
#include "Session.h"
#include <stdexcept>
#include <fstream>
#include <stack>
#include <algorithm>
#include <filesystem>
int Session::nextId = 0;

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
        Image* copy = images.top()->clone();
        history.push(copy);
    }
    
    images.push(image);
}
void Session::loadImage(const std::string& filename) {
    Image* newImage = ImageFactory::create(filename);
    addImage(newImage);
}

void Session::closeImage() {
    if (images.empty()) {throw std::runtime_error("No images to close");}
    delete images.top();
    images.pop();
}

std::vector<Image*> Session::getImages() const {
    std::vector<Image*> result;
    std::stack<Image*> tempStack = images;
    while (!tempStack.empty()) {
        result.push_back(tempStack.top());
        tempStack.pop();
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
    images.top()->save(filename);
}

void Session::saveFirstFileAs(const std::string& newFileName) const {
    if(images.empty()){throw std::runtime_error("No images in session");}
    std::stack<Image*> tempStack = images;
    Image* firstImage = nullptr;
    while (!tempStack.empty()) {
        firstImage = tempStack.top();
        tempStack.pop();
    }
    
    if(firstImage){firstImage->save(newFileName);
    } 
    else{throw std::runtime_error("Failed to access first image");}
}

void Session::terminate() {
    active = false;
    clearImages();
    clearTransformations();
    clearHistory();
}
void Session::printSessionInfo(std::ostream& out) const {
    out << "Session ID: " << id << "\n"
        << "Status: " << (active ? "Active" : "Inactive") << "\n"
        << "Images count: " << images.size() << "\n"
        << "Pending transformations: " << transformations.size() << "\n";
}
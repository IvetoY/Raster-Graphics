#include "Session.h"
#include <stdexcept>
Session::Session(int _id) : id(_id) {}
void Session::addImage(std::unique_ptr<Image> image){
    images.push_back(std::move(image));
}

void Session::addTransformation(std::unique_ptr<Transformations> transformation){
    pendingTransformations.push_back(std::move(transformation));
}
void Session::applyTransformations(){
    for(auto& img: images){
        for(auto& transformation: pendingTransformations){
            if(img && transformation){
            transformation->apply(*img);
            //da se dobavi history
            }
        }
    }
    pendingTransformations.clear();
}
int Session::getId() const{return id;}
const std::vector<std::unique_ptr<Image>>& Session::getImages() const {return images;}
const std::vector<std::unique_ptr<Transformations>>& Session::getPendingTransformations() const {
    return pendingTransformations;
}
void Session::undo(){
    if(history.empty()){throw std::runtime_error("Undo history is empty!");}
    for (auto& img : images) {
        Image* lastState = history.top();
        *img = *lastState;
        history.pop();
        delete lastState;
    }
}
Session::~Session() {
    while (!history.empty()) {
        delete history.top();
        history.pop();
    }
}
bool Session::isActive() const{return active;}
void Session::terminate(){active = false;}
/*void Session::saveImage(const String& filePath){
    if(images.empty()){throw std::runtime_error("No images to save");}
    
}*/


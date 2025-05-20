#include "Load.h"
#include "../Session/Session.h"
#include "../Image/ImageFactory.h"

void Load::apply(Session& session){
    auto image = ImageFactory::create(filePath);
    if(!image){
        throw std::runtime_error("Failed to load image");
    }
    session.addImage(std::move(image));
}

void Load::undo(Session& session){
    /*to be done*/
}
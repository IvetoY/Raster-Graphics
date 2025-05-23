#include "Add.h"
#include "../Session/Session.h"
explicit Add::Add(Image* img) : image(img) {
        if(img == nullptr){throw std::invalid_argument("Add command: nullptr image provided");}
}

void Add::apply(Session& session) {
        if (image == nullptr) {throw std::runtime_error("Add command: Image pointer is null");}
        session.addImage(image->clone());
    }
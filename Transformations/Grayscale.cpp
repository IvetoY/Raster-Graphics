#include "../Transformations/Transformations.h"
#include "../Image/Image.h"
#include "../Pixel/Pixel.h"
#include "Grayscale.h"
#include <cstring>
#include "../System/System.h"
void Grayscale::apply(System& system) const {
    auto& sessions = system.getSessions();
    int activeSessionID = system.getActiveSessionId();

    for (Session* session : sessions) {
        if (session->getId() == activeSessionID) {
            for (Image* img : session->getImages()) {
                img->grayscale();
            }
            return;
        }
    }
    throw std::runtime_error("Active session not found!");
}
Grayscale* Grayscale::clone() const{
    return new Grayscale(*this);
}

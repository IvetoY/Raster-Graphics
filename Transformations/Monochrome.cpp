#include "Monochrome.h"
#include "../Image/Image.h"
#include "../Pixel/Pixel.h"
#include "../System/System.h"
void Monochrome::apply(System& system) const {
    auto& sessions = system.getSessions();
    int activeSessionID = system.getActiveSessionId();

    for (Session* session : sessions) {
        if (session->getId() == activeSessionID) {
            for (Image* img : session->getImages()) {
                img->monochrome();
            }
            return;
        }
    }
    throw std::runtime_error("Active session not found!");
}

Monochrome* Monochrome::clone() const{
    return new Monochrome(*this);
}
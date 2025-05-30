#include "Rotate.h"
#include "../Image/PBM.h"
#include "../Image/PPM.h"
#include "../Image/PGM.h"
#include "../Image/ImageFactory.h"
#include <algorithm>
#include <stdexcept>
#include "../Session/Session.h"
#include "../System/System.h"
Rotate::Rotate(Direction _d) : direction(_d) {
    if(_d!=left && _d!=right){
        throw std::invalid_argument("Invalid rotation direction. Use left or right");
    }
}
void Rotate::apply(System& system) const {
    auto& sessions = system.getSessions();
    int activeSessionID = system.getActiveSessionId();

    for (Session* session : sessions) {
        if (session->getId() == activeSessionID) {
            for (Image* img : session->getImages()) {
                if (direction == left) img->rotateLeft();
                else img->rotateRight();
            }
            return;
        }
    }
    throw std::runtime_error("Active session not found!");
}

Rotate* Rotate::clone() const{
    return new Rotate(*this);
}

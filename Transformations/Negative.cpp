#include "Negative.h"
#include "../System/System.h"
void Negative::apply(System& system) const {
    auto& sessions = system.getSessions();
    int activeSessionID = system.getActiveSessionId();

    for (Session* session : sessions) {
        if (session->getId() == activeSessionID) {
            for (Image* img : session->getImages()) {
                img->negative();
            }
            return;
        }
    }
    throw std::runtime_error("Active session not found!");
}
Negative* Negative::clone() const {
    return new Negative(*this);
}
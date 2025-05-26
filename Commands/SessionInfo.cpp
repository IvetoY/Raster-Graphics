#include "SessionInfo.h"

Commands* SessionInfo::clone() const{return new SessionInfo(*this);}

void SessionInfo::apply(System& system) const{
    system.printSessionInfo();
}


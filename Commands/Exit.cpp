#include "Exit.h"
#include "../System/System.h"

void Exit::apply(System& system) const {
    system.exitProgram();
}
Commands* Exit::clone() const{return new Exit(*this);}
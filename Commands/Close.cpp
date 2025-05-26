#include "Close.h"
#include "../System/System.h"
#include <iostream>
void Close::apply(System& system) const{
    system.closeSession();
}
Commands* Close::clone() const {return new Close(*this);}
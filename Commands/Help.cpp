#include "Help.h"
#include "../System/System.h"
#include <iostream>
Commands* Help::clone() const{return new Help(*this);}
void Help::apply(System& system) const{
    system.help(std::cout);
}
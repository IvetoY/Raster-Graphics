#include "Undo.h"

void Undo::apply(System& system) const{
    std::cout << "Executing Undo command..." << std::endl;
    system.undo();
}
Commands* Undo::clone() const{return new Undo(*this);}
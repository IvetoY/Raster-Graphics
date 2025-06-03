#include "Undo.h"
#include "../System/System.h"
void Undo::apply(System& system) const{
    system.undo();
}
Commands* Undo::clone() const{return new Undo(*this);}
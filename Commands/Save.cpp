#include "Save.h"
#include "../System/System.h"

Save::Save() {}
void Save::apply(System& system) const{
    system.saveSession();
}
Commands* Save::clone() const{return new Save(*this);}


#include "Save.h"
#include "../System/System.h"
Save::Save(const String& filename) : filename(filename) {}
void Save::apply(System& system) const{
    System& system = System::getInstance();
    system.saveSession(filename);
}
Commands* Save::clone() const{return new Save(*this);}


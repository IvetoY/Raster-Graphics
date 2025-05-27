#include "Save.h"
#include "../System/System.h"

Save::Save(const std::string& filename) : filename(filename) {}
void Save::apply(System& system) const{
    system.saveSession(filename);
}
Commands* Save::clone() const{return new Save(*this);}


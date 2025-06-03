#include "Load.h"
#include "../System/System.h"
#include <string>
#include <vector>
Load::Load(const std::vector<std::string>& files) : files(files){}
void Load::apply(System& system) const {
    system.loadSession(this->files);
}
Commands* Load::clone() const{return new Load(*this);}

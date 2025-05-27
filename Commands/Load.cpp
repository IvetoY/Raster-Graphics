#include "Load.h"
#include "../System/System.h"
#include <vector>
#include <string>
Load::Load(std::string&& files) : file(std::move(files)){}
Load::Load(const std::string& files) : file(files){}
void Load::apply(System& system) const {
    system.loadSession(this->file);
}
Commands* Load::clone() const{return new Load(*this);}

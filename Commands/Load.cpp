#include "Load.h"
#include "../System/System.h"
#include <vector>
Load::Load(std::vector<String>&& files) : files(std::move(files)){}
Load::Load(const std::vector<String>& files) : files(files){}
void Load::apply(System& system) const {
    system.loadSession(this->files);
}
Commands* Load::clone() const{return new Load(*this);}

#include "../Commands/Add.h"
#include "../System/System.h"

void Add::apply(System& system) const {
        system.addImageToSession(this->filename);
}
Add::Add(const std::string& fileName) : filename(fileName){}

Add::Add(std::string && fileName) : filename(std::move(fileName))
{}

Commands* Add::clone() const{return new Add(*this);}
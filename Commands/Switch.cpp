#include "Switch.h"
#include "../System/System.h"

Switch::Switch(int _switchTo) : switchTo(_switchTo){}

void Switch::apply(System& system) const{
	system.switchSession(this->switchTo);
}
Switch::Switch(const std::string& idStr) {
        try {
            switchTo= std::stoi(idStr);
        } catch (...) {
            throw std::invalid_argument("Invalid session ID");
        }
    }

Commands* Switch::clone() const{return new Switch(*this);}
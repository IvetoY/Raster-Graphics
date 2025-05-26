#include "Switch.h"
#include "../System/System.h"

Switch::Switch(int _switchTo) : switchTo(_switchTo){}

void Switch::apply(System& system) const{
	system.switchSession(this->switchTo);
}

Commands* Switch::clone() const{return new Switch(*this);}
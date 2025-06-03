#pragma once
#include "../System/System.h"
#include <string>
class System;
class Commands{
public:
virtual ~Commands() = default;
virtual void apply(System& system) const = 0;
virtual Commands* clone() const = 0;
virtual std::string getCommandName() const = 0;
virtual std::string getCommandDescription() const = 0;
};

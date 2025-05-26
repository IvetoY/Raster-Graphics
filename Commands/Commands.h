#pragma once
#include "../System/System.h"
#include "../Structures/String/String.h"
class System;
class Commands{
public:
virtual ~Commands() = default;
virtual void apply(System& system) const = 0;
virtual Commands* clone() const = 0;
virtual String getCommandName() const = 0;
virtual String getCommandDescription() const = 0;
};
#pragma once
#include <vector>
#include "../String/String.h"
class Session;
class Commands{
public:
virtual ~Commands() = default;
virtual void apply(Session& session) = 0;
virtual void undo(Session& session) = 0;
virtual String getCommandName() const = 0;
virtual String getCommandDescription() const = 0;
};
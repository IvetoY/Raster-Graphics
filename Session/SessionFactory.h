#pragma once
#include "Session.h"
#include <memory>

class SessionFactory{
public:
static std::unique_ptr<Session> createSession(int id) {
    return std::make_unique<Session>(id);
}
};
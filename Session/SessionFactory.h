#pragma once
#include "Session.h"
#include <memory>

class SessionFactory{
public:
static Session* createSession(int id) {
    return new Session(id);
}
};
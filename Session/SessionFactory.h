#pragma once
#include "Session.h"

class SessionFactory{
public:
static Session* createSession(int id) {
    return new Session(id);
}
};
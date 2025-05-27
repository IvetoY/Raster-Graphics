#pragma once 
#include "Session.h"

class SessionManager{
    
    static SessionManager* instance;
    
    int next = 1;
    SessionManager() = default;
    public:
    static SessionManager& getInstance(){
        static SessionManager instance;
        return instance;
    }
    
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
};


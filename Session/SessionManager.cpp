#pragma once 
#include "Session.h"
#include <memory>
#include <unordered_map>

class SessionManager{
    
    static SessionManager* instance;
    std::unordered_map<int, std::unique_ptr<Session>> sessions;
    int next = 1;
    SessionManager() = default;
    public:
    static SessionManager& getInstance(){
        static SessionManager instance;
        return instance;
    }
    int createSession(){
        int _id = next ++;
        sessions[_id] = std::make_unique<Session>(_id);
        return _id; 
    }
    Session& getSession(int id) {
        auto it = sessions.find(id);
        if (it == sessions.end()) {
            throw std::runtime_error("Session not found");
        }
        return *(it->second);
    }
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
};


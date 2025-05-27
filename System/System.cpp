#include "System.h"
#include "../Session/Session.h"
#include <algorithm>
#include <cstring>
#include "../Image/ImageFactory.h"
System& System::getInstance(){
    static System system;
    return system;
}
int System::createNewSession() {
    Session* newSession = new Session();
    sessions.push_back(newSession);
    return sessionCounter++;
}

System::~System() {
    for (Session* session : sessions) {
        delete session;
    }
    sessions.clear();
}
void System::queueTransformation(Transformations* transformation) {
    if (activeSessionID == -1) {throw std::runtime_error("No active sessions!");}
    int index = findSession();
    if(index == -1){throw std::runtime_error("Current session not found!");}
    sessions[index]->queueTransformation(transformation);
}
int System::findSession()const{
    for (size_t i = 0; i < sessions.size(); ++i){
        if (sessions[i]->getId() == activeSessionID) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
void System::saveSession(const std::string& filename){
	if (activeSessionID == -1){throw std::runtime_error("No active sessions!");}
	int index = findSession();
	sessions[index]->saveFirstFileAs(filename);
}
void System::saveSessionFileAs(const std::string& newFileName){
	if (activeSessionID == -1){throw std::runtime_error("No active sessions!");}
	int index = findSession();
	sessions[index]->saveFirstFileAs(newFileName);
}
void System::printSessionInfo() const{
	if (activeSessionID == -1){throw std::runtime_error("No active sessions!");}
	int index = findSession();
	sessions[index]->printSessionInfo(std::cout);
}
void System::loadSession(const std::string& files) {
        int newSessionId = createNewSession();
        
            Image* img = ImageFactory::create(files); 
            sessions[newSessionId]->addImage(img);
        
        activeSessionID = newSessionId;
    }
void System::loadSession(const std::vector<std::string>& files) {
        int newSessionId = createNewSession();
        for (const auto& file : files) {
            Image* img = ImageFactory::create(file); 
            sessions[newSessionId]->addImage(img);
        }
        activeSessionID = newSessionId;
    }

void System::help(std::ostream& out) const {
    out << "Available commands:\n"
        << "  load <file1> [file2...] - Load files into new session\n"
        << "  switch <id>            - Switch to session with given ID\n"
        << "  undo                   - Undo last operation in current session\n"
        << "  save                   - Save current session\n"
        << "  saveas <filename>      - Save current session with new name\n"
        << "  add <filename>         - Add image to current session\n"
        << "  info                   - Show current session info\n"
        << "  close                  - Close current session\n"
        << "  exit                   - Exit the program\n";
}

void System::undo() {
    int currentIdx = findSession();
    if (currentIdx != -1) {
        sessions[currentIdx]->undo();
    }
}
void System::addImageToSession(const std::string& fileName) {
    int currentIdx = findSession();
    Image* newImage = ImageFactory::create(fileName);
    if (currentIdx != -1) {
        sessions[currentIdx]->addImage(newImage);
    } else {
        throw std::runtime_error("No active session to add image to");
    }
}
void System::switchSession(int newID){
	if (activeSessionID == -1)
		throw std::runtime_error("No active sessions!");

	for (size_t i = 0; i < sessions.size(); i++){
		if (sessions[i]->getId() == newID){
			activeSessionID = newID;
			std::cout << "Switched to session with ID " << newID << std::endl;
			return;
		}
	}

	throw std::runtime_error("Session not found! Check if ID is correct.");
}
void System::closeSession() {
    if (activeSessionID == -1) {
        throw std::runtime_error("No active session to close!");
    }

    int index = findSession();
    if (index == -1) {
        throw std::runtime_error("Current session not found!");
    }
    delete sessions[index];
    sessions.erase(sessions.begin() + index);

    if (sessions.empty()) {
        activeSessionID = -1;
    } else {
        activeSessionID = sessions[0]->getId();
    }
}

void System::exitProgram() {running = false;}

bool System::isRunning() const {return running;} 
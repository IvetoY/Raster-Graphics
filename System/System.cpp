#include "System.h"
#include "../Session/Session.h"
#include <algorithm>
#include <cstring>
#include "../Image/ImageFactory.h"
System* System::instance = nullptr;
System& System::getInstance(){
    static System system;
    return system;
}
System::System() : activeSessionID(-1), running(true) {}

System::~System() {
    for (Session* session : sessions) {
        delete session;
    }
    sessions.clear();
}

int System::createNewSession() {
    Session* newSession = new Session();
    sessions.push_back(newSession);
    
    if (activeSessionID == -1) {
        activeSessionID = newSession->getId();
    }
    
    return newSession->getId();
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


void System::saveSession() {
    if (activeSessionID == -1) {
        throw std::runtime_error("No active sessions!");
    }
    
    int index = findSession();
    if (index == -1) {
        throw std::runtime_error("Current session not found!");
    }

    std::vector<Image*> sessionImages = sessions[index]->getImages();
    if (sessionImages.empty()) {
        throw std::runtime_error("No images to save in current session!");
    }
    for (size_t i = 0; i < sessionImages.size(); ++i) {
        try {
            std::string file = sessionImages[i]->getFileName();
            
            if (file.empty()) {
                throw std::runtime_error("Image has no original filename");
            }

            if (sessionImages[i]->getMagicNumber() == "P4" || 
                sessionImages[i]->getMagicNumber() == "P5" ||
                sessionImages[i]->getMagicNumber() == "P6") {
                sessionImages[i]->saveBinary(file);
            } else {
                sessionImages[i]->saveASCII(file);
            }
            
            std::cout << "Successfully saved: " << file << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Failed to save image " << i+1 << ": " << e.what() << std::endl;
        }
    }
}
void System::saveSessionFileAs(const std::string& newFileName){
	if (activeSessionID == -1){throw std::runtime_error("No active sessions!");}
	int index = findSession();
	sessions[index]->saveFirstFileAs(newFileName);
}
void System::printSessionInfo() const {
    if (activeSessionID == -1) {
        throw std::runtime_error("No active sessions!");
    }
    
    int index = findSession();
    if (index == -1) {
        throw std::runtime_error("Current session not found!");
    }
    
    std::cout << "=== System Session Info ===\n";
    sessions[index]->printSessionInfo(std::cout);
    std::cout << "Total sessions: " << sessions.size() << "\n";
    std::cout << "Active session ID: " << activeSessionID << "\n";
    std::cout << "=========================\n";
}
void System::loadSession(const std::string& file) {
    std::ifstream testFile(file);
    if (!testFile.is_open()) {
        throw std::runtime_error(("File does not exist or cannot be opened: " + file).c_str());
    }
    testFile.close();
    int newSessionId = createNewSession();
    Session* newSession = sessions.back();
    
        Image* img = ImageFactory::create(file);
        
        newSession->addImage(img);
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
        << "  session info           - Show current session info\n"
        << "  close                  - Close current session\n"
        << "  exit                   - Exit the program\n"
        << "  help                   - Show this help message\n\n"
        << "Available transformations:\n"
        << "  grayscale              - Convert images to grayscale\n"
        << "  monochrome             - Convert images to black and white\n"
        << "  negative               - Invert image colors\n"
        << "  rotate <left|right>    - Rotate images 90 degrees\n";
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

    int closingId = activeSessionID;
    delete sessions[index];
    sessions.erase(sessions.begin() + index);

    if (sessions.empty()) {
        activeSessionID = -1;
    } else {
        activeSessionID = sessions[0]->getId();
    }
    std::cout << "Closed session with ID " << closingId << "\n";
    if (activeSessionID != -1) {
        std::cout << "New active session ID: " << activeSessionID << "\n";
    }
}

void System::exitProgram() {running = false;}

bool System::isRunning() const {return running;} 
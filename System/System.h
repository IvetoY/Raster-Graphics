#pragma once
#include <vector>
#include <cstring>
#include "../Structures/String/String.h"
#include "../Session/Session.h"
class Session;
class Transformations;
class System{
private:
	static System* instance;
	std::vector<Image*> images;
    std::vector<Session*> sessions;
	int activeSessionID = -1;
	bool running = true;
	System();
	
public:
	int findSession() const;
	static System& getInstance();
	~System();

	std::vector<Image*>& getImages() { return images; }
    const std::vector<Image*>& getImages() const { return images; }

	std::vector<Session*>& getSessions() { return sessions; }
    const std::vector<Session*>& getSessions() const { return sessions; }

	int getActiveSessionId() {return activeSessionID;}
	
	System(const System&) = delete;
	System& operator=(const System&) = delete;
	
	int createNewSession();
	void queueTransformation(Transformations* transformation);
	void saveSession();
	void loadSession(const std::vector<std::string>& files);
	void help(std::ostream& out) const;
	void switchSession(int newID);
	void printSessionInfo() const;
	void closeSession();
    void undo();
    

	void addImageToSession(const std::string& fileName);
	void saveSessionFileAs(const std::string& newFileName);

	
	//void applyTransformation();

	bool isRunning() const;
    void exitProgram();
	void loadSession(const std::string& files);

};
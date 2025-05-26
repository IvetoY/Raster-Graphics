#pragma once
#include <vector>
#include "../Structures/String/String.h"
#include "../Session/Session.h"
class Session;
class System{
private:
	int sessionCounter =0;
    std::vector<Session*> sessions;
	int activeSessionID = -1;
	bool running = true;
	System() = default;
	int findSession() const;
public:
	static System& getInstance();
	System(const System&) = delete;
	System& operator=(const System&) = delete;
	~System();
	
	void loadSession(const std::vector<String>& files);
	void help(std::ostream& out) const;
	void switchSession(int newID);
	void saveSession(const String& filename);
	void printSessionInfo() const;
	void closeSession();
    void undo();
    int createNewSession();

	void addImageToSession(const String& fileName);
	void saveSessionFileAs(const String& newFileName);

	void queueTransformation(Transformations* transformation);
	//void applyTransformation();

	bool isRunning() const;
    void exitProgram();


};
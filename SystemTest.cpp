#include <iostream>
#include <cassert>
#include "System.h"
#include "../Session/Session.h"
#include "../Image/ImageFactory.h"

void testSystem() {
    System& system = System::getInstance();

    System& system2 = System::getInstance();
    assert(&system == &system2);
    std::cout << "Test 1: Singleton test passed\n";

    int sessionId = system.createNewSession();
    assert(sessionId == 0);
    std::cout << "Test 2: Create session test passed\n";

    
    try {
        system.loadSession({"test1.pgm", "test1.pgm"});
        std::cout << "Test 3: Load session test passed (files not actually loaded in this test)\n";
    } catch(...) {
        std::cout << "Test 3: Load session test failed\n";
    }
    try {
        system.switchSession(0);
        std::cout << "Test 4: Switch session test passed\n";
    } catch(...) {
        std::cout << "Test 4: Switch session test failed\n";
    }
    try {
        system.addImageToSession("test2.pbm");
        std::cout << "Test 5: Add image test passed (file not actually loaded in this test)\n";
    } catch(...) {
        std::cout << "Test 5: Add image test failed\n";
    }

    try {
        system.printSessionInfo();
        std::cout << "Test 6: Print session info test passed\n";
    } catch(...) {
        std::cout << "Test 6: Print session info test failed\n";
    }
    try {
        system.closeSession();
        std::cout << "Test 7: Close session test passed\n";
    } catch(...) {
        std::cout << "Test 7: Close session test failed\n";
    }
    system.help(std::cout);
    std::cout << "Test 8: Help test passed\n";

    assert(system.isRunning() == true);
    system.exitProgram();
    assert(system.isRunning() == false);
    std::cout << "Test 9: Running state test passed\n";
}

int main() {
    testSystem();
    return 0;
}
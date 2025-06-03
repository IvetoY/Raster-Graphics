#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../System/System.h"
#include "../Image/Image.h"

std::stringstream test_output;

void testLoadAndSaveImage() {
  
    Session::resetSessionCounter();
    {
        std::ofstream testFile("test.ppm");
    }

    System& system = System::getInstance();
    system.createNewSession();
    system.loadSession("test.ppm");
    
    auto images = system.getImages();
    assert(images.size() == 1 && "Error : Expected 1 image!");
    assert(images[0]->getFileName() == "test.ppm" && "Error: Inavlid file name!");

    auto old_cout = std::cout.rdbuf(test_output.rdbuf());
    
    system.saveSession();
    
    std::cout.rdbuf(old_cout);
    
    std::string output = test_output.str();
    assert(output.find("Successfully saved") != std::string::npos && 
           "Error: Missing successfully saved message!");

    
    std::cout << "All test passed!\n";
}

int main() {
    try {
        testLoadAndSaveImage();
        return 0;
    } catch(const std::exception& e) {
        std::cerr << "Test failed : " << e.what() << std::endl;
        return 1;
    }
}
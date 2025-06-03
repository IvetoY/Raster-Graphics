#include "SaveAs.h"
#include "../System/System.h"
#include <sstream>
#include <iostream>
SaveAs::SaveAs(const std::string& _newFileName) 
    : newFileName(_newFileName) {}

void SaveAs::apply(System& system) const {
    Session* session = system.getCurrentSession();
    if (!session) {throw std::runtime_error("No active session");}
    
    session->applyTransformations(system);

    std::vector<Image*> images = session->getImages();
    if (images.empty()) {throw std::runtime_error("No images to save");}

    size_t dotPos = newFileName.find_last_of(".");
    std::string stem = newFileName;
    std::string extension = "";

    if (dotPos != std::string::npos) {
        stem = newFileName.substr(0, dotPos);
        extension = newFileName.substr(dotPos);
    }

    for (size_t i = 0; i < images.size(); ++i) {
        std::string numberedFilename;
        if (images.size() > 1) {
            std::ostringstream oss;
            oss << stem << "_" << (i+1) << extension;
            numberedFilename = oss.str();
        } else {
            numberedFilename = newFileName;
        }

        try {
            const std::string& magic = images[i]->getMagicNumber();
            if (magic == "P1" || magic == "P2" || magic == "P3") {
                images[i]->saveASCII(numberedFilename);
            } else {
                images[i]->saveBinary(numberedFilename);
            }
            std::cout << "Successfully saved as: " << numberedFilename << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error saving " << numberedFilename << ": " << e.what() << std::endl;
            throw;
        }
    }
}

Commands* SaveAs::clone() const {
    return new SaveAs(*this);
}

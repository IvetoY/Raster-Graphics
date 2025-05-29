#include "Commands/Commands.h"
#include "Commands/Load.h"
#include "Commands/Save.h"
#include "Commands/Add.h"
#include "Commands/Close.h"
#include "Commands/Exit.h"
#include "Commands/Help.h"
#include "Commands/SessionInfo.h"
#include "Commands/Switch.h"
#include "Commands/Undo.h"
#include "Transformations/Grayscale.h"
#include "Transformations/Monochrome.h"
#include "Transformations/Negative.h"
#include "Transformations/Rotate.h"
#include <iostream>
#include <string>

int main() {
    System& system = System::getInstance();
    std::string userInput;
    
    while (system.isRunning()) {
        std::cout << "> ";
        std::getline(std::cin, userInput);
        
        if(userInput.empty()) { continue; }
        
        size_t space_pos = userInput.find(' ');
        std::string command = userInput.substr(0, space_pos);
        std::string args = (space_pos != std::string::npos) ? userInput.substr(space_pos + 1) : "";
        
        Transformations* transformation = nullptr;
        
        if(command == "grayscale") {
            transformation = new Grayscale();
            transformation->apply(system);
            delete transformation;
        }
        else if(command == "monochrome") {
            transformation = new Monochrome();
            transformation->apply(system);
            delete transformation;
        }
        else if(command == "negative") {
            transformation = new Negative();
            transformation->apply(system);
            delete transformation;
        }
        else if(command == "rotate") {
            if(!args.empty()) {
                if(args == "left") {
                    transformation = new Rotate(Rotate::left);
                    transformation->apply(system);
                    delete transformation;
                } 
                else if(args == "right") {
                    transformation = new Rotate(Rotate::right);
                    transformation->apply(system);
                    delete transformation;
                }
                else {
                    std::cerr << "Error: Invalid rotation direction. Use 'left' or 'right'\n";
                }
            }
            else {
                std::cerr << "Error: Missing rotation direction\n";
            }
        }
        else if(command == "load") {
            if(!args.empty()) {
                Commands* cmd = new Load(args);
                cmd->apply(system);
                delete cmd;
            } 
            else {
                std::cerr << "Error: Missing file path for load command\n";
            }
        }
        else if(command == "save") {
            Commands* cmd = new Save();
            cmd->apply(system);
            delete cmd;
        }
        else if(command == "add") {
            if(!args.empty()) {
                Commands* cmd = new Add(args);
                cmd->apply(system);
                delete cmd;
            }
            else {
                std::cerr << "Error: Missing image path for add command\n";
            }
        }
        else if(command == "close") {
            Commands* cmd = new Close();
            cmd->apply(system);
            delete cmd;
        }
        else if(command == "exit") {
            Commands* cmd = new Exit();
            cmd->apply(system);
            delete cmd;
        }
        else if(command == "help") {
            Commands* cmd = new Help();
            cmd->apply(system);
            delete cmd;
        }
        else if(command == "session" && args == "info") {
            Commands* cmd = new SessionInfo();
            cmd->apply(system);
            delete cmd;
        }
        else if(command == "switch") {
            if (!args.empty()) {
                Commands* cmd = new Switch(args);
                cmd->apply(system);
                delete cmd;
            } 
            else {
                std::cerr << "Error: Missing session ID for switch command\n";
            }
        }
        else if(command == "undo") {
            Commands* cmd = new Undo();
            cmd->apply(system);
            delete cmd;
        }
        else {
            std::cerr << "Error: Unknown command '" << command << "'\n";
        }
        
        
    }
    
    return 0;
}
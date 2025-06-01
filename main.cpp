#include "Commands/Commands.h"
#include "Commands/Load.h"
#include "Commands/Save.h"
#include "Commands/SaveAs.h"
#include "Commands/Add.h"
#include "Commands/Close.h"
#include "Commands/Exit.h"
#include "Commands/Help.h"
#include "Commands/SessionInfo.h"
#include "Commands/Switch.h"
#include "Commands/Undo.h"
#include "Commands/Collage.h"
#include "Transformations/Grayscale.h"
#include "Transformations/Monochrome.h"
#include "Transformations/Negative.h"
#include "Transformations/Rotate.h"
#include <iostream>
#include <string>
#include <sstream>
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
            system.queueTransformation(transformation);
        }
        else if(command == "monochrome") {
            transformation = new Monochrome();
            system.queueTransformation(transformation);
        }
        else if(command == "negative") {
            transformation = new Negative();
            system.queueTransformation(transformation);
        }
        else if(command == "rotate") {
            if (!args.empty()) {
        try {
            Rotate::Direction dir = (args == "left") ? Rotate::left : Rotate::right;
            transformation = new Rotate(dir);
            system.queueTransformation(transformation);
        } catch (const std::exception& e) {
            std::cerr << "Rotation error: " << e.what() << "\n";
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
            Session* session = system.getCurrentSession();
            session->applyTransformations(system);
            Commands *cmd = new Save();
            cmd->apply(system);
            delete cmd;
        }
        else if(command == "saveas") {
            if (!args.empty())
            {
                Commands *cmd = new SaveAs(args);
                cmd->apply(system);
                delete cmd;
            }
            else
            {
                std::cerr << "Error: Missing filename for saveas command\n";
            }
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
        else if (command == "collage")
        {
            std::vector<std::string> argsList;
            std::istringstream iss(args);
            std::string arg;

            while (iss >> arg)
            {
                argsList.push_back(arg);
            }

            if (argsList.size() == 4)
            {
                try
                {
                    Direction dir;
                    if (argsList[2] == "horizontal")
                    {
                        dir = Direction::HORIZONTAL;
                    }
                    else if (argsList[2] == "vertical")
                    {
                        dir = Direction::VERTICAL;
                    }
                    else
                    {
                        throw std::invalid_argument("Invalid direction. Use 'horizontal' or 'vertical'");
                    }

                    Image *img1 = system.findImageInCurrentSession(argsList[0]);
                    Image *img2 = system.findImageInCurrentSession(argsList[1]);

                    Commands *cmd = new Collage(img1, img2, dir, argsList[3]);
                    cmd->apply(system);
                    delete cmd;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }
            else
            {
                std::cerr << "Error: collage command requires 4 arguments - <image1> <image2> <direction>  <outimage>\n";
            }
        }
        else
        {
            std::cerr << "Error: Unknown command '" << command << "'\n";
        }
    }

    return 0;
}
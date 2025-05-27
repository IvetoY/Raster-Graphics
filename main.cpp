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
#include <iostream>
#include <string>
//да добавя трансформациите 
int main() {
    System& system = System::getInstance();
    std::string userInput;
    
    while (system.isRunning()){
        std::cout << "> ";
        std::getline(std::cin, userInput);
        
        if(userInput.empty()){continue;}
        
        Commands* cmd = nullptr;
        size_t space_pos = userInput.find(' ');
        std::string command = userInput.substr(0, space_pos);
        std::string args = (space_pos != std::string::npos) ? userInput.substr(space_pos + 1) : "";
        
        if(command == "load"){
            if(!args.empty()){cmd = new Load(args);} 
            else{std::cerr << "Error: Missing file path for load command\n";}
        }
        else if(command == "save"){cmd = new Save();}
        else if(command == "add"){
            if(!args.empty()){cmd = new Add(args);}
            else{std::cerr << "Error: Missing image path for add command\n";}
        }
        else if(command == "close"){cmd = new Close();}
        else if(command == "exit"){cmd = new Exit();}
        else if(command == "help"){cmd = new Help();}
        else if(command == "session" && args == "info"){cmd = new SessionInfo();}
        else if(command == "switch"){
            if (!args.empty()){cmd = new Switch(args);} 
            else{std::cerr << "Error: Missing session ID for switch command\n";}
        }
        else if(command == "undo"){cmd = new Undo();}
        else {std::cerr << "Error: Unknown command '" << command << "'\n";}
        
        if(cmd != nullptr){
            cmd->apply(system);
            delete cmd;
        }
    }
    
    return 0;
}
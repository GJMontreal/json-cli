#ifndef INCLUDE_COMMAND_DISPATCHER_HPP
#define INCLUDE_COMMAND_DISPATCHER_HPP


#include "Command.h"
#include <unordered_map>
#include <memory>

class CommandDispatcher {
  public:
      void register_command(std::unique_ptr<Command> cmd);
  
      void execute(const std::string& input) const;
       {
          auto space = input.find(' ');
          std::string cmd_name = input.substr(0, space);
          std::string arg = (space == std::string::npos) ? "" : input.substr(space + 1);
  
          auto it = commands_.find(cmd_name);
          if (it != commands_.end()) {
              it->second->execute(arg);
          } else {
              std::cout << "Unknown command: " << cmd_name << "\n";
          }
      }
  
  private:
      std::unordered_map<std::string, std::unique_ptr<Command>> commands_;
  };

  #endif

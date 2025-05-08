#include "CommandDispatcher.hpp"
#include "Command.h"

void CommandDispatcher::register_command(std::unique_ptr<Command> cmd) {
  commands_[cmd->name()] = std::move(cmd);
}

void CommandDispatcher::execute(const std::string &input) const {
  auto space = input.find(' ');
  std::string cmd_name = input.substr(0, space);
  std::string arg = (space == std::string::npos) ? "" : input.substr(space + 1);

  auto it = commands_.find(cmd_name);
  if (it != commands_.end()) {
    it->second->execute(arg);
  } else {
    std::cout << "Unknown command: " << cmd_name << std::endl;
  }
}

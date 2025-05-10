#include "Command.h"

#include <iostream>

void HelpCommand::execute(const nlohmann::json json) const  {
    std::cout << "Help" << std::endl ;
}

void GreetCommand::execute(const std::string &name) const {
  std::cout << this->context() << name << "!\n";
}

void DebugCommand::execute(const nlohmann::json json) const  {
  auto config = this->context();
  if(json.contains("verbose") && json["verbose"].is_boolean()){
    config->verbose = json["verbose"].get<bool>();
  }
  if(json.contains("echo") && json["echo"].is_boolean()){
    config->echo = json["echo"].get<bool>();
  }
}

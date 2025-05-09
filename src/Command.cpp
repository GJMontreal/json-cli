#include "Command.h"

#include <iostream>

void HelpCommand::execute(const nlohmann::json json) const  {
    std::cout << "Help" << std::endl ;
}

void GreetCommand::execute(const std::string &name) const {
  std::cout << this->context() << name << "!\n";
}

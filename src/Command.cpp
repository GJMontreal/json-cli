#include "Command.h"

#include <nlohmann/json.hpp>
#include <iostream>

void HelpCommand::execute(std::any arg) const  {
  if (const auto* json = std::any_cast<nlohmann::json>(&arg)){
    std::cout << "Help" << std::endl ;
  }else{
    //invalid argument
  }
}

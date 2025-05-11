
#include "Command.h"
#include "pico/stdlib.h"
#include <pico/error.h>
#include <stdio.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "InputHandler.h"
#include "CommandDispatcher.hpp"

using json = nlohmann::json;

template<typename Dispatcher>
void dispatch_json_value(Dispatcher& dispatcher, const std::string& command, const json& value) {
  if (value.is_number_integer()) {
      dispatcher.dispatch(command, value.get<int>());
  } else if (value.is_number_float()) {
      dispatcher.dispatch(command, value.get<double>());
  } else if (value.is_boolean()) {
      dispatcher.dispatch(command, value.get<bool>());
  } else if (value.is_string()) {
      dispatcher.dispatch(command, value.get<std::string>());
  } else {
      dispatcher.dispatch(command, value);
  }
}

int main() {
    stdio_init_all();
        
    std::cout << "Initializing CLI" << std::endl;

    DEFINE_SELF_REFERENTIAL_DISPATCHER(MyCLI, GreetCommand, DebugCommand)
    auto config = std::make_shared<DebugConfiguration>(DebugConfiguration{false,false});

    auto debug = std::make_shared<DebugCommand>(config);
    auto greet = std::make_shared<GreetCommand>("Bienvenue ");
    auto help = std::make_shared<ListCommandsCommand<MyCLI>>();

    MyCLI dispatcher(greet, debug, help);
    // help.set_context(std::ref(dispatcher));

    InputHandler input_handler;
    
    while(1){
      char c = getchar_timeout_us(0);
      if(c != char(PICO_ERROR_TIMEOUT)){
        nlohmann::json json;

        if(input_handler.handle(c, json)){ 
          if(config->echo){
            std::cerr << json.dump(4) << std::endl;
          }
          std::string top_command = json.begin().key();
          dispatch_json_value(dispatcher,top_command, json[top_command]); 
          if(config->verbose){
            std::cout << "debug " << config->verbose << std::endl;
          }         
        }
      }
    }
    return 0;
}


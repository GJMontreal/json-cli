
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

    GreetCommand greet("hello");
    HelpCommand help;

    CommandDispatcher dispatcher(greet,help);
    InputHandler input_handler;

    
    while(1){
      char c = getchar_timeout_us(0);
      if(c != char(PICO_ERROR_TIMEOUT)){
        nlohmann::json json;

        if(input_handler.handle(c, json)){ 
          std::cerr << json.dump(4) << std::endl;
          std::string top_command = json.begin().key();
          dispatch_json_value(dispatcher,top_command, json[top_command]);          
        }
      }
    }
    return 0;
}


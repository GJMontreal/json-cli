#include "InputHandler.h"

#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

void InputHandler::handle(char c){
  if (c == '{') {
    if(!started){
      json_stream.str("");
      json_stream.clear();
    }
    brace_count()++;
    started = true;
  }else if (c == '}'){
    brace_count()--;
  }else if ( c == 0x03 ){
    std::cout << "reseting" << std::endl;
    brace_count()=0;
    started=false;
  }

  if(started){
    std::cout << c ;
    json_stream << c;
    if (brace_count() == 0) {
      started = false;
      try{
        json j = json::parse(json_stream.str(),nullptr,false);
        std::cout << "Parsed JSON:\n" << j.dump(4) << std::endl;
      }catch(const json::parse_error& e) {
            std::cerr << "Parse error: " << e.what() << std::endl;
        // how could we check for an error at this point?
        
      }
    }
  }
}
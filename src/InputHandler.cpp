#include "InputHandler.h"

#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

// return either a complete json object or null

void InputHandler::handle(char c, json &j){
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
    brace_count()=0;
    started=false;
  }

  if(started){
    json_stream << c;
    if (brace_count() == 0) {
      started = false;
      try{
        j = json::parse(json_stream.str(),nullptr,false);
      }catch(const json::parse_error& e) {
            std::cerr << "Parse error: " << e.what() << std::endl;
      }
    }
  }
 
}
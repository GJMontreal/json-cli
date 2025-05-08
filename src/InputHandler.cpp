#include "InputHandler.h"

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// return either a complete json object or null

bool InputHandler::handle(char c, json &j) {
  if (c == '{') {
    if (!started) {
      json_stream.str("");
      json_stream.clear();
    }
    brace_count()++;
    started = true;
  } else if (c == '}') {
    brace_count()--;
  } else if (c == 0x03) {
    brace_count() = 0;
    started = false;
  }

  if (started) {
    json_stream << c;
    if (brace_count() == 0) {
      started = false;
      j = json::parse(json_stream.str(), nullptr, false);
      return !(j.is_discarded() || j.empty());  // we're not using exceptions so it will never be empty
    }
  }
  return false;
}
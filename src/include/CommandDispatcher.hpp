#ifndef INCLUDE_COMMAND_DISPATCHER_HPP
#define INCLUDE_COMMAND_DISPATCHER_HPP


#include "Command.h"
#include <tuple>
#include <string>
#include <variant>
#include <iostream>
#include <utility>

using CommandArg = std::variant<std::string, int, nlohmann::json>;

template<typename... Commands>
class CommandDispatcher {
  public:
      CommandDispatcher(Commands...cmds): commands_(std::move(cmds)...) {}

      void dispatch(const std::string& cmd_name, const CommandArg& arg) const {
        std::apply([&](const auto&... commands){
        (..., try_execute(commands, cmd_name, arg));}, commands_);
    }
  
      void dispatch(const std::string& name, const char* cstr) const {
        dispatch(name, std::string(cstr));
    }
  private:
      std::tuple<Commands...> commands_;

      template <typename Cmd>
      static void try_execute(const Cmd& cmd, const std::string& name, const CommandArg& arg)
       {
          using ExpectedType = typename Cmd::ArgType;

          if (name != Cmd::name) {
            return;
          }

          if (auto* actual = std::get_if<ExpectedType>(&arg)) {
            cmd(*actual);  // Safe
        } else {
            std::cerr << "Type mismatch for command '" << name << "'\n";
        }
      }

  };

  #endif

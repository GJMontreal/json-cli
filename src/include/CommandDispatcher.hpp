#ifndef INCLUDE_COMMAND_DISPATCHER_HPP
#define INCLUDE_COMMAND_DISPATCHER_HPP


#include "Command.h"
#include <tuple>
#include <string>
#include <variant>
#include <iostream>
#include <utility>

// Simplify the creation of our CRTP 
// pass in the command class names wanted
// It will append a ListCommandsCommand
#define DEFINE_SELF_REFERENTIAL_DISPATCHER(name, ...)                        \
    struct name;                                                             \
    using name##Commands = CommandDispatcher<__VA_ARGS__, ListCommandsCommand<name>>; \
    class name : public name##Commands {                                     \
    public:                                                                   \
        using name##Commands::name##Commands;                                \
    };

using CommandArg = std::variant<std::monostate,std::string, int, nlohmann::json>;

template<typename... Commands>
class CommandDispatcher {
public:
  CommandDispatcher(std::shared_ptr<Commands>... cmds)
      : commands_(cmds...) {}

  void dispatch(const std::string &cmd_name, const CommandArg &arg) const {
    bool matched = false;

    std::apply(
        [&](const auto &...command) {
          (..., (matched = matched || try_execute(*command, cmd_name, arg)));
        },
        commands_);

    if (!matched) {
      std::cerr << "No command matched: \"" << cmd_name << "\"\n";
    }
    }
  
    std::tuple<std::shared_ptr<Commands>...>& get_commands() {
      return commands_;
    }
//is this next even used?
      void dispatch(const std::string& name, const char* cstr) const {
        dispatch(name, std::string(cstr));
    }
  private:
      std::tuple<std::shared_ptr<Commands>...> commands_;

      template <typename Cmd>
      static bool try_execute(const Cmd& cmd, const std::string& name, const CommandArg& arg)
       {
          using ExpectedType = typename Cmd::ArgType;

          if (name != Cmd::name) {
            return false;
          }

          if (auto* actual = std::get_if<ExpectedType>(&arg)) {
            cmd(*actual);  // Safe
        } else {
            std::cerr << "Type mismatch for command '" << name << "'\n";
        }
        return true;
      }

  };

  #endif

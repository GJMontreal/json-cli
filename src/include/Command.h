#ifndef INCLUDE_COMMAND_HPP
#define INCLUDE_COMMAND_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

// this is hard to read Derived should be T, T should be ArgType
template <typename Derived, typename T, typename Context = std::monostate>
class Command {
public:
  using ArgType = T;
  using ContextType = Context;

  Command(Context context = Context{}) : context_(std::move(context)) {}

  void operator()(const T &t) const {
    static_cast<const Derived &>(*this).execute(t);
  }

  void set_context(Context new_context) { context_ = std::move(new_context); }
  
protected:
  const Context &context() const { return context_; }
  Context &context() { return context_; }


private:
  mutable Context context_;
};

// get rid of this
class HelpCommand : public Command<HelpCommand, nlohmann::json> {
public:
  static constexpr const char *name = "help";

  void execute(const nlohmann::json json) const;
};

class GreetCommand : public Command<GreetCommand, std::string, std::string> {
public:
  static constexpr const char *name = "greet";
  static constexpr const char *description = "Echoes a greeting";

  using Command<GreetCommand, std::string, std::string>::Command;

  void execute(const std::string &arg) const;
};

struct DebugConfiguration {
  bool verbose = false;
  bool echo = false;
};

class DebugCommand : public Command<DebugCommand, nlohmann::json,
                                    std::shared_ptr<DebugConfiguration>> {
public:
  static constexpr const char *name = "debug";
  static constexpr const char *description = "sets debugging options";

  using Command<DebugCommand, nlohmann::json,
                std::shared_ptr<DebugConfiguration>>::Command;

  void execute(const nlohmann::json) const;
};

template <typename Dispatcher>
class ListCommandsCommand
    : public Command<ListCommandsCommand<Dispatcher>, std::monostate,
                     std::optional<std::reference_wrapper<Dispatcher>>> {
public:
  static constexpr const char *name = "help";
  static constexpr const char *description = "Lists available commands";

  using Base = Command<ListCommandsCommand<Dispatcher>, std::monostate,
                       std::optional<std::reference_wrapper<Dispatcher>>>;
  using Base::Base;

  void execute(const std::monostate &) const {
    auto &dispatcher = this->context().get();

    std::apply(
        [](const auto &...cmds) {
          ((std::cout << "- " << std::decay_t<decltype(cmds)>::name << ": "
                      << std::decay_t<decltype(cmds)>::description << "\n"),
           ...);
        },
        dispatcher.get_commands());
  }
};

#endif

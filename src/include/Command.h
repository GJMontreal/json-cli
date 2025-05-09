#ifndef INCLUDE_COMMAND_HPP
#define INCLUDE_COMMAND_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <variant>
#include <utility>
#include <type_traits>

template <typename Derived, typename T, typename Context = std::monostate> 
class Command {
public:
  using ArgType = T;
  using ContextType = Context;

  Command(Context context = Context{}) : context_(std::move(context)) {}

  void operator()(const T &t) const {
    static_cast<const Derived &>(*this).execute(t);
  }

  protected:
   const Context& context() const {return context_;}
  
  private:
   Context context_;
};

class HelpCommand : public Command<HelpCommand, nlohmann::json> {
public:
  static constexpr const char *name = "help";
  
  void execute(const nlohmann::json json) const;
};

class GreetCommand : public Command<GreetCommand, std::string, std::string> {
public:
  static constexpr const char *name = "greet";
  
  using Command<GreetCommand, std::string, std::string>::Command;

  void execute(const std::string& arg) const;
};

class AnotherCommand : public Command<AnotherCommand, int> {
public:
  static constexpr const char *name = "test";

  void execute(const int& arg) const { std::cout << "test, " << arg << "!\n"; }
};

#endif

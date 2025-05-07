#include <iostream>
#include <sstream>
#include <string>
#include <csignal>
#include <atomic>
#include "external/json.hpp"

using json = nlohmann::json;

class SignalHandler {
public:
    static std::atomic<bool>& interrupted() {
        static std::atomic<bool> flag{false};
        return flag;
    }

    static void handle(int) {
        interrupted() = true;
        std::cerr << "\n[INFO] Received SIGINT (Ctrl+C), exiting...\n";
    }

    static void setup() {
        std::signal(SIGINT, handle);
    }
};

int main() {
    SignalHandler::setup();

    std::string line;
    std::stringstream json_stream;
    int brace_count = 0;
    bool started = false;

    while (!SignalHandler::interrupted() && std::getline(std::cin, line)) {
        for (char c : line) {
            if (c == '{') {
                brace_count++;
                started = true;
            } else if (c == '}') {
                brace_count--;
            }
        }

        if (started) {
            json_stream << line << '\n';
        }

        if (started && brace_count == 0) {
            break;
        }
    }

    if (SignalHandler::interrupted()) {
        return 1;
    }

    try {
        json j = json::parse(json_stream.str());
        std::cout << "Parsed JSON:\n" << j.dump(4) << std::endl;
    } catch (const json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

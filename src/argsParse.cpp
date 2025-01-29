#include "../include/argsParse.h"

bool InputParser::argsDigester(int argc, char *argv[]) {
  if (argc > 3) {
    return false;
  } else {
    for (size_t i; i < argc; i++) {
      unparsed.push_back(argv[i]);
    }
    return true;
  }
}

void InputParser::argsTranslate(const std::vector<std::string> &a) {
  if (a.empty()) {
    parsed.push_back(ArgsType::FILES);
  } else {
    for (auto arg : a) {
      if (arg == "help" || arg == "--h" || arg == "--help") {
        parsed.push_back(ArgsType::HELP);
        continue;
      }
      if (arg == "version" || arg == "--v" || arg == "--version") {
        parsed.push_back(ArgsType::VERSION);
        continue;
      }
      if (arg == "file") {
        parsed.push_back(ArgsType::FILES);
        continue;
      }
      if (arg == "dir") {
        parsed.push_back(ArgsType::DIR);
        continue;
      }
      parsed.push_back(ArgsType::UNKNOWN);
    }
  }
}

std::vector<ArgsType> InputParser::getArgs() { return parsed; }

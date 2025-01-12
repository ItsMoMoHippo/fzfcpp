#include "../include/help.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

enum ArgType {
  HELP,
  VERSION,
  DIR,
  FILES,
  UNKNOWN,
};

ArgType getArgType(const std::string &args) {
  if (args == "help" || args == "man") {
    return HELP;
  }
  if (args == "version") {
    return VERSION;
  }
  if (args == "dir") {
    return DIR;
  }
  if (args == "file") {
    return FILES;
  }
  return UNKNOWN;
}

void printList(const std::vector<std::string> &, const std::filesystem::path &,
               bool &);

int main(int argc, char *argv[]) {

  std::cout << "args was " << argv[1] << '\n';
  std::filesystem::path currentDir = std::filesystem::current_path();
  std::cout << "CWD: " << currentDir.string() << "\n\n";

  bool helpFlag = false, dirFlag = false, fileFlag = false, isFile = false;

  for (int i = 1; i < argc; ++i) {
    switch (getArgType(argv[i])) {
    case HELP:
      helpFlag = true;
      break;
    case DIR:
      dirFlag = true;
      break;
    case FILES:
      fileFlag = true;
      break;
    case VERSION:
      std::cout << "VERSION 1.0";
      break;
    case UNKNOWN:
      std::cout << "Unknown flag inputted: " << argv[i];
      break;
    default:
      fileFlag = true;
      break;
    }
  }

  if (helpFlag) {
    // help options
    if (dirFlag) {
      // dir help
      printDirHelp();
    } else if (fileFlag) {
      // file help
      printFilesHelp();
    } else {
      // general help
      printGeneralHelp();
    }
  } else if (dirFlag) {
    // search dirs
  } else if (fileFlag) {
    // search files
  }
}

void printList(const std::vector<std::string> &entryList,
               const std::filesystem::path &currentWorkingDirectory,
               bool &isFile) {
  if (isFile) {
    for (const auto &entry : entryList) {
      std::cout << currentWorkingDirectory.string() << "\\" << entry << "\n";
    }
  } else {
    for (const auto &entry : entryList) {
      std::cout << currentWorkingDirectory.string() << "\\" << entry << "\\\n";
    }
  }
}

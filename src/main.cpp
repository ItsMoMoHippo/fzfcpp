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

// functions declerations
ArgType getArgType(const std::string &args);

void printList(const std::vector<std::string> &, const std::filesystem::path &,
               bool &);

void searchDir(const std::filesystem::path &currentWorkingDirectory,
               std::vector<std::string> &, bool &isFile);

// main
int main(int argc, char *argv[]) {

  std::filesystem::path currentDir = std::filesystem::current_path();
  std::cout << "CWD: " << currentDir.string() << "\n\n";

  bool helpFlag = false, dirFlag = false, fileFlag = false, isFile = false;
  std::vector<std::string> entryList;
  std::vector<std::string> filteredList;

  if (argc == 1) {
    fileFlag = true;
  } else {
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
    std::cout << "dir search" << '\n';
    isFile = false;
    searchDir(currentDir, entryList, isFile);
    printList(entryList, currentDir, isFile);
  } else if (fileFlag) {
    // search files
    std::cout << "file search" << '\n';
    isFile = true;
    searchDir(currentDir, entryList, isFile);
    printList(entryList, currentDir, isFile);
  }
}

// function implementation
/* @param = string,
 * @return = enum,
 * converts arguments into enum for processing */
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

/* @ param = std::vector<std::string>,
 *           std::filesystem::path,
 *           bool,
 * @return = void,
 * prints out given vector, used for printing out file paths */
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

/* @param = std::vector<std::string>,
 *          std::filesystem::path,
 *          bool,
 * @return = void,
 * searches the given directory and then appends each valid result to vector */
void searchDir(const std::filesystem::path &currentWorkingDirectory,
               std::vector<std::string> &entryList, bool &isFile) {
  for (const auto &entry :
       std::filesystem::recursive_directory_iterator(currentWorkingDirectory)) {
    if ((isFile && std::filesystem::is_regular_file(entry)) ||
        (!isFile && std::filesystem::is_directory(entry))) {
      entryList.push_back(entry.path().string());
    }
  }
}

#include "../include/help.h"
#include <conio.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
// #include "../include/argsParse.h"

enum ArgType {
  HELP,
  VERSION,
  DIR,
  FILES,
  UNKNOWN,
};

// functions declerations
ArgType getArgType(const std::string &);
void searchDir(const std::filesystem::path &, std::vector<std::string> &,
               bool &);
bool getDynamicInput(std::string &);
std::vector<std::string> filteredResultEntries(const std::vector<std::string> &,
                                               const std::string &);
void displayResults(const std::vector<std::string> &);
void printAllEntries(const std::vector<std::string> &);

// main
int main(int argc, char *argv[]) {

  std::filesystem::path currentDir = std::filesystem::current_path();
  bool helpFlag = false, dirFlag = false, fileFlag = false, isFile = false;
  std::vector<std::string> entryList;
  std::vector<std::string> filteredList;

  // args parsing
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

  // program execution dependent on flags
  std::string input;
  std::string cache;
  if (helpFlag) {
    // help options
    if (dirFlag) {
      printDirHelp();
    } else if (fileFlag) {
      printFilesHelp();
    } else {
      printGeneralHelp();
    }
  } else if (dirFlag) {
    std::cout << "dir search" << '\n';
    isFile = false;
    searchDir(currentDir, entryList, isFile);
    system("cls");
    printAllEntries(entryList);
    while (true) {
      if (!getDynamicInput(input)) {
        break;
      }
      if (input != cache) {
        displayResults(filteredResultEntries(entryList, input));
        std::cout << input;
        cache = input;
      }
    }
  } else if (fileFlag) {
    std::cout << "file search" << '\n';
    isFile = true;
    searchDir(currentDir, entryList, isFile);
    system("cls");
    printAllEntries(entryList);
    while (true) {
      if (!getDynamicInput(input)) {
        break;
      }
      if (input != cache) {
        displayResults(filteredResultEntries(entryList, input));
        std::cout << input;
        cache = input;
      }
    }
  }
  system("cls");
  return 0;
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

/* @param = std::string
 * @return = bool
 * with a std::string used for editable strind, is used to read console input
 * used for filtering, bool is to indicate if `escape` is pressed as to exit the
 * program */
bool getDynamicInput(std::string &input) {
  if (_kbhit()) {
    char ch = _getch();
    if (ch == '\b') {
      if (!input.empty()) {
        input.pop_back();
        std::cout << "\b\b";
      }
    } else if (ch == '\r') {
    } else if (ch == '\e') {
      return false;
    } else {
      input += ch;
      std::cout << ch;
    }
  }
  return true;
}

/* @param = std::vector<std::string>,
 *          std::string
 * @return = std::vector<std::string>
 * filters a list of strings with an input string,
 * this is the fuzzy finding part */
std::vector<std::string>
filteredResultEntries(const std::vector<std::string> &entries,
                      const std::string &input) {
  std::vector<std::string> filteredList;
  for (const auto &entry : entries) {
    int spot = 0;
    bool valid = true;

    for (const char &c : input) {
      spot = entry.find(c, spot);
      if (spot == std::string::npos) {
        valid = false;
        break;
      }
      ++spot;
    }
    if (valid) {
      filteredList.push_back(entry);
    }
  }
  return filteredList;
}

/* @param = std::vector<std::string>
 * @return = void
 * prints filtered results to console after clearing screen */
void displayResults(const std::vector<std::string> &results) {
  system("cls");
  if (results.size() > 100) {
    for (int i = 0; i < 100; i++) {
      std::cout << results[i] << '\n';
    }
  } else {
    for (const auto &result : results) {
      std::cout << result << '\n';
    }
  }
}

/* @param = std::vector<std::string>
 * @return = void
 * prints all strings in list to console */
void printAllEntries(const std::vector<std::string> &entries) {
  if (entries.size() > 100) {
    for (int i = 0; i < 100; i++) {
      std::cout << entries[i] << '\n';
    }
  } else {
    for (const auto &entry : entries) {
      std::cout << entry << '\n';
    }
  }
}

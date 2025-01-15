#include "../include/help.h"
#include <iostream>

void printGeneralHelp() {
  std::cout
      << "FZFC is a C++ implementation of FZF, a fuzzy finder" << '\n'
      << "To use the application type 'fzfc' (or optional fzfc files) to "
         "do the default search all files in working directory"
      << '\n'
      << "likewise type 'fzfc dir' to search all directories in the "
         "working directory"
      << '\n'
      << "do 'fzfc version' to print version in use" << '\n'
      << "or 'fzfc (optional) help' for info of a command" << '\n'
      << "in both cases, results will be filtered by user input (non-exact)"
      << '\n';
};
void printDirHelp() {
  std::cout << "fzfc dir" << '\n'
            << "this mode searches through the working directory and displays "
               "all sub-directories"
            << '\n'
            << "folders will be filtered out with user input" << '\n';
};
void printFilesHelp() {
  std::cout << "fzfc files" << '\n'
            << "this mode searches through the working directory and displays "
               "all files"
            << '\n'
            << "folders will be filtered out with user input" << '\n';
};

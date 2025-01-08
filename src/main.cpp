#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

void printList(const std::vector<std::string> &, const std::filesystem::path &);

int main() {
  std::filesystem::path currentDir = std::filesystem::current_path();
  std::cout << "CWD: " << currentDir.string() << "\n\n";

  std::cout << "choose what to do:\n";
  int choice;
  std::cin >> choice;
  std::cout << "\n";

  std::vector<std::string> itemsList;
  std::string temp;
  switch (choice) {
  case 2:
    for (const auto &entry : std::filesystem::directory_iterator(currentDir)) {
      if (!std::filesystem::is_directory(entry.status())) {
        itemsList.push_back(entry.path().filename().string());
      }
    }
    printList(itemsList, currentDir);
    break;
  default:
    // list all directories
    for (const auto &entry : std::filesystem::directory_iterator(currentDir)) {
      if (std::filesystem::is_directory(entry.status())) {
        itemsList.push_back(entry.path().filename().string());
      }
    }
    printList(itemsList, currentDir);
  }
  return 0;
}

void printList(const std::vector<std::string> &a,
               const std::filesystem::path &b) {
  for (const auto &entry : a) {
    std::cout << b.string() << "\\" << entry << '\n';
  }
}

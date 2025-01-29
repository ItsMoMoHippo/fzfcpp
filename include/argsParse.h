#ifndef ARGSPARSE_H

#define ARGSPARSE_H

#include <string>
#include <vector>

enum class ArgsType { HELP, VERSION, FILES, DIR, UNKNOWN };

class InputParser {
public:
  /* takes in the command line arguments */
  bool argsDigester(int argc, char *argv[]);

  /* translates the char arrays to enums */
  void argsTranslate(const std::vector<std::string> &);

  /* getter for passed args */
  std::vector<ArgsType> getArgs();

private:
  std::vector<std::string> unparsed;
  std::vector<ArgsType> parsed;
};

#endif // !ARGSPARSE_H

#include <iostream>

bool getInput(std::string& input)
{
  std::cout << "$ ";
  std::getline(std::cin, input);
  if (input.size() > 0)
    return true;
  
  return false;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::string input;
  while (getInput(input))
    if (input == "exit 0")
      return 0;
    else
      std::cout << input << ": command not found\n";
}

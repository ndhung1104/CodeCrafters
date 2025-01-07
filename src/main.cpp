#include <iostream>

bool getInput(std::string& input)
{
  std::cout << "$ ";

  std::string input;
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
  // if (input == "invalid_command")
    std::cout << input << ": command not found";
}

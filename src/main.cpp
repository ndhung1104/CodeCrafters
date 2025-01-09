#include <iostream>
#include <unordered_map>
#include <sstream>
#include <filesystem>

bool getInput(std::string& input)
{
  std::cout << "$ ";
  std::getline(std::cin, input);
  if (input.size() > 0)
    return true;
  
  return false;
}

int handleInput(const std::string& input, const std::unordered_map<std::string, int>& commandMap, std::string& arguments)
{
  std::stringstream ss(input);
  std::string firstArg;
  std::getline(ss, firstArg, ' ');
  arguments = "";
  if (firstArg.size() != input.size())
    arguments = input.substr(firstArg.size() + 1);
  auto it = commandMap.find(firstArg);
  if (it != commandMap.end()) 
  {
    return it->second;
  }
  return -1;
}

void checkPath(const std::string& input)
{
  std::string systemPath = std::getenv("PATH");
  std::stringstream ss(systemPath);
  std::string path;
  while(!ss.eof())
  {
      getline(ss, path, ':');
      std::string abs_path = path + '/' + input;
      if(std::filesystem::exists(abs_path))
      {
          std::cout << input << " is " << abs_path << std::endl;
          return;
      }
  }

  std::cout << input << ": not found\n";
}

void checkCommand(const std::string& input, const std::unordered_map<std::string, int>& commandMap)
{
  auto it = commandMap.find(input);
  if (it != commandMap.end()) 
  {
    std::cout << input << " is a shell builtin\n";
  }
  else
    checkPath(input);
}



int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::unordered_map<std::string, int> commandMap = 
  {
    {"exit", 0},
    {"echo", 1},
    {"type", 2}
  };

  // Uncomment this block to pass the first stage
  std::string input, argument;
  while (getInput(input))
  {
    switch (handleInput(input, commandMap, argument)) 
    {
      case 0:
        return 0;
      case 1:
        std::cout << argument << "\n";
        break;
      case 2:
        checkCommand(argument, commandMap);
        break;
      default:
        std::cout << input << ": command not found\n";
        break;
    }
    
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
  }
    
      
}

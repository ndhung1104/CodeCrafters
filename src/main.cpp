#include <iostream>
#include <unordered_map>
#include <sstream>
#include <filesystem>
#include <cstdlib>

bool getInput(std::string& input)
{
  std::cout << "$ ";
  std::getline(std::cin, input);
  if (input.size() > 0)
    return true;
  
  return false;
}

int handleInput(const std::string& input, const std::unordered_map<std::string, int>& commandMap, std::string& command, std::string& arguments)
{
  std::stringstream ss(input);
  std::getline(ss, command, ' ');
  arguments = "";
  if (command.size() != input.size())
    arguments = input.substr(command.size() + 1);
  auto it = commandMap.find(command);
  if (it != commandMap.end()) 
  {
    return it->second;
  }
  return -1;
}

std::string checkPath(const std::string& input)
{
  std::string systemPath = std::getenv("PATH");
  std::stringstream ss(systemPath);
  std::string path;
  while(!ss.eof())
  {
      getline(ss, path, ':'); // getline(ss, path, ';'); for window
      std::string abs_path = path + '/' + input;
      if(std::filesystem::exists(abs_path))
        return abs_path;
  }
  return "";
}

void checkCommand(const std::string& input, const std::unordered_map<std::string, int>& commandMap)
{
  auto it = commandMap.find(input);
  if (it != commandMap.end()) 
  {
    std::cout << input << " is a shell builtin\n";
  }
  else
  {
    std::string abs_path = checkPath(input);
    if (abs_path.size() > 0)
      std::cout << input << " is " << abs_path << std::endl;
    else
      std::cout << input << ": not found\n";
  }
}

bool checkExecutable(const std::string& command, const std::string& argument)
{
  std::string abs_path = checkPath(command);
  if (abs_path.size() == 0)
    return false;
  
  // std::string cmd = "\"" + abs_path + "\" " + argument;
  std::string cmd = command + " " + argument;
  if (std::system(cmd.c_str()) == 0)
    return true;
  
  return false;
}

void getCurrentPath()
{
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::cout << currentPath << std::endl;
}



int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::unordered_map<std::string, int> commandMap = 
  {
    {"exit", 0},
    {"echo", 1},
    {"type", 2},
    {"pwn", 3}
  };

  // Uncomment this block to pass the first stage
  std::string input, argument, command;
  while (getInput(input))
  {
    switch (handleInput(input, commandMap, command, argument)) 
    {
      case 0:
        return 0;
      case 1:
        std::cout << argument << "\n";
        break;
      case 2:
        checkCommand(argument, commandMap);
        break;
      case 3:
        getCurrentPath();
        
        break;
      default:
        if (checkExecutable(command, argument) == false)
          std::cout << input << ": command not found\n";
        break;
    }
    
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
  }
    
      
}

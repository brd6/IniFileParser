#include <iostream>
#include "IniFileParser.hpp"

int main(int ac, char **av)
{
  if (ac != 2)
    {
      std::cerr << "Usage: " << av[0] << " file.ini" << std::endl;
      return 1;
    }
  ini::IniFileParser iniFileParser;

  try
    {
      iniFileParser.load(av[1]);
//      auto section = iniFileParser.getSection("global");
  //  iniFileParser.get("sectionName", "key", value);
  //  std::string val = iniFileParser.get("sectionName", "key");

      std::vector<std::vector<std::string>> ss;
//      std::string ss;

      iniFileParser.get("mySection", "mapOfNumber", ss);
      std::cout << ss[0][0] << std::endl;
    }
  catch (std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }

  return 0;
}
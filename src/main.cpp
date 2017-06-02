#include <iostream>
#include "IniFileParser.hpp"

int main()
{
  ini::IniFileParser iniFileParser;

  try
    {
      iniFileParser.load("./test_files/save.ini");
//      auto section = iniFileParser.getSection("global");
  //  iniFileParser.get("sectionName", "key", value);
  //  std::string val = iniFileParser.get("sectionName", "key");

//      std::vector<std::vector<std::string>> ss;
//      std::string ss;

      std::cout << iniFileParser.get("Save", "text") << std::endl;

      iniFileParser.set("Save", "text", "Berdrigue");

      std::cout << iniFileParser.get("Save", "text") << std::endl;

      iniFileParser.saveToFile();
    }
  catch (std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }

  return 0;
}
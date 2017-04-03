//
// Created by brd6 on 01/04/17.
//

#include <iostream>
#include <algorithm>
#include "IniSection.hpp"

namespace ini
{
  IniSection::IniSection()
  {

  }

  IniSection::IniSection(std::string const &name) :
	  mName(name)
  {
  }

  IniSection::IniSection(std::string const &name, std::vector<std::string> const &lines) :
	  mName(name),
	  mLines(lines)
  {

  }

  std::string const &IniSection::getName() const
  {
    return mName;
  }

  void IniSection::setName(std::string const &name)
  {
    mName = name;
  }

  void IniSection::feed(std::string const &line)
  {
    mLines.push_back(line);
  }

  void IniSection::parse()
  {
    std::string key;
    std::string value;

    for (auto &line : mLines)
      {
	if (isANewDataLine(line))
	  key = extractKey(line);
	value = extractValue(line);

	if (mData.count(key) == 0)
	  mData[key] = value;
	else
	  {
	    mData[key].append("\n");
	    mData[key].append(value);
	  }
      }
  }

  bool IniSection::isANewDataLine(std::string const &currentLine) const
  {
    auto sep = currentLine.find_first_of(DATA_SEPARATOR);

    return sep != std::string::npos && sep > 0;
  }

  std::string IniSection::extractKey(std::string const &line) const
  {
    std::string buff;

    auto sepPos = line.find_first_not_of(SPACES_SYMBOL);
    if (sepPos == std::string::npos)
      throw std::logic_error("Invalid key separator position : '" + line + "'");

    buff = line.substr(sepPos, line.size());

    sepPos = buff.find_first_of(DATA_SEPARATORS);
    if (sepPos == std::string::npos)
      throw std::logic_error("Invalid key separator position : '" + buff + "'");

    return buff.substr(0, sepPos);
  }

  std::string IniSection::extractValue(std::string const &line) const
  {
    std::string buff;

    auto sepPos = line.find_first_of(DATA_SEPARATOR);
    if (sepPos == std::string::npos && isANewDataLine(line))
      throw std::logic_error("Invalid key separator position : '" + line + "'");
    buff = line.substr(sepPos + 1, line.size());
    sepPos = buff.find_first_not_of(SPACES_SYMBOL);
    if (sepPos == std::string::npos)
      throw std::logic_error("Not value found: '" + line + "'");
    return buff.substr(sepPos, buff.size());
  }

  std::string const IniSection::get(std::string const &key) const
  {
    if (mData.count(key) == 0)
      return "";
    return mData.at(key);
  }

  std::string& IniSection::trimSpace(std::string &str) const
  {
    // remove start space
    auto startPos = str.find_first_not_of(SPACES_SYMBOL);
    if(std::string::npos != startPos)
      str = str.substr(startPos);
    // remove last space
    auto endPos = str.find_last_not_of(SPACES_SYMBOL);
    if( std::string::npos != endPos)
	str = str.substr(0, endPos + 1);
    return str;
  }

}
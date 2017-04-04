//
// Created by brd6 on 01/04/17.
//

#include <iostream>
#include <fstream>
#include "IniFileParser.hpp"

namespace ini
{
  IniFileParser::IniFileParser():
	  mCurrentSection(nullptr),
	  mFilePath("")
  {

  }

  IniFileParser::IniFileParser(const std::string &filePath):
	  mCurrentSection(nullptr),
	  mFilePath(filePath)
  {
    load(filePath);
  }

  void IniFileParser::load(std::string const &filePath)
  {
    mFilePath = filePath;
    std::ifstream inFile(filePath);
    mNbSection = 0;
    mNbLine = 0;
    std::string currentLine;

    if (!inFile.is_open())
      throw std::runtime_error("Unable to read the file to do the parsing.");

    while (std::getline(inFile, currentLine))
      {
	if (isAEmptyLine(currentLine) || isAComment(currentLine))
	  continue;
	if (!parse(currentLine))
	  {
	    inFile.close();
	    throw std::logic_error("Not section found. Your file must start with a section name. : '" +
				   currentLine + "'");
	  }
	mNbLine++;
      }
    checkLastLine(currentLine);
    inFile.close();
  }

  void IniFileParser::saveToFile(std::string const &filePath)
  {
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);

    if (!outFile.is_open())
      throw std::runtime_error("Unable to open the file to do save.");

    for (auto &section : mSections)
      {
	outFile << "[" << section->getName() << "]" << std::endl;
	for (auto &content : section->getContents())
	  {
	    outFile << content.first << " = " << content.second << std::endl;
	  }
	outFile << std::endl;
      }

    outFile.close();
  }

  void IniFileParser::saveToFile()
  {
    saveToFile(mFilePath);
  }

  void IniFileParser::checkLastLine(std::string &currentLine)
  {
    if (mNbLine > 1)
      addNewSection(mCurrentSection);
    else
      throw std::logic_error("Empty section content. : '" + currentLine + "'");
  }

  bool IniFileParser::parse(std::string const &currentLine)
  {
    std::string sectionName;
    bool isASection = isAStartingSection(currentLine, sectionName);

    if (mNbLine == 0 && !isASection)
      return false;
    if (mNbLine > 1 && isASection)
      {
	addNewSection(mCurrentSection);
	mNbLine = 0;
      }
    if (mNbLine == 0 && isASection)
      {
	mCurrentSection = new IniSection(sectionName);
	mNbSection++;
      }
    if (!isASection)
      mCurrentSection->feed(currentLine);
    return true;
  }

  void IniFileParser::addNewSection(IniSection *section)
  {
    section->parse();
    std::unique_ptr<IniSection> sectionPtr(section);

    mSections.push_back(std::move(sectionPtr));
  }

  bool IniFileParser::isAComment(std::string const &line) const
  {
    auto firstCharPos = line.find_first_not_of(SPACES_SYMBOL);

    if (firstCharPos == std::string::npos)
      return false;
    return (line[firstCharPos] == COMMENT_SYMBOLS[0] ||
	    line[firstCharPos] == COMMENT_SYMBOLS[1]);
  }

  bool IniFileParser::isAEmptyLine(std::string const &line) const
  {
    auto firstCharPos = line.find_first_not_of(SPACES_SYMBOL);

    return firstCharPos == std::string::npos;
  }

  bool IniFileParser::isAStartingSection(std::string const &line, std::string &sectionName) const
  {
    auto firstCharPos = line.find_first_of(SECTION_DELIMITER[0]);
    auto lastCharPos = line.find_first_of(SECTION_DELIMITER[1]);

    if (firstCharPos == std::string::npos ||
	lastCharPos == std::string::npos)
      return false;
    firstCharPos++;
    auto sectionNameLength = lastCharPos - firstCharPos;
    if (sectionNameLength < 1)
      return false;
    sectionName = line.substr(firstCharPos, sectionNameLength);
    return true;
  }

  void IniFileParser::unload()
  {
    mSections.clear();
    mCurrentSection = nullptr;
  }

  IniSection *IniFileParser::getSection(std::string const &name) const
  {
    auto section = std::find_if(std::begin(mSections),
				std::end(mSections),
				[name](auto &currentSection) {
				  return currentSection->getName() == name;
				});

    if (section == std::end(mSections))
      throw std::logic_error("Section '" + name + "' not found.");
    return section->get();
  }

  std::string const IniFileParser::get(std::string const &sectionName, std::string const &key)
  {
    auto section = getSection(sectionName);

    return (section == nullptr) ? "" : section->get(key);
  }

  void IniFileParser::set(std::string const &sectionName, std::string const &key, std::string const &value)
  {
    auto section = getSection(sectionName);

    if (section == nullptr)
      throw std::logic_error("Section '" + sectionName + "' not found");
    section->set(key, value);
  }

}
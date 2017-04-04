//
// Created by brd6 on 01/04/17.
//

#ifndef _IniFileParser_H_
#define _IniFileParser_H_

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "IniSection.hpp"

namespace ini
{
  /**
   * An ini file parser.
   * Handling simple data type : int, float, char, string, bool, array.
   * You can use comment in your ini file by starting the line by ; or #
   * In case of error, an exception is throwing.
   */
  class IniFileParser
  {
   private:
    const char DATA_SEPARATOR = '=';
    const char ARRAY_SEPARATOR = ',';
    const std::string COMMENT_SYMBOLS = "#;";
    const std::string SPACES_SYMBOL = " \t";
    const std::string DEFAULT_SECTION_NAME = "_";
    const std::string SECTION_DELIMITER = "[]";

    std::vector<std::unique_ptr<IniSection>> mSections;

    int mNbSection;
    int mNbLine;
    IniSection *mCurrentSection;

    std::string mFilePath;

   public:
    IniFileParser();
    IniFileParser(std::string const &filePath);
    IniFileParser(IniFileParser const &) = delete;
    IniFileParser &operator=(IniFileParser const &) = delete;
    virtual ~IniFileParser() = default;

    void load(std::string const &filePath);

    void unload();

    void saveToFile(std::string const &filePath);
    void saveToFile();

    IniSection *getSection(std::string const &name) const;

    template<typename TValue>
    void get(std::string const &sectionName, std::string const &key, TValue &value) const
    {
      auto section = getSection(sectionName);

      if (section == nullptr)
	throw std::logic_error("Section '" + sectionName + "' not found");
      section->get<TValue>(key, value);
    }

    template<typename TValue>
    void get(std::string const &sectionName, std::string const &key, std::vector<TValue> &value) const
    {
      auto section = getSection(sectionName);

      if (section == nullptr)
	throw std::logic_error("Section '" + sectionName + "' not found");
      section->getArray<TValue>(key, value);
    }

    template<typename TValue>
    void get(std::string const &sectionName, std::string const &key, std::vector<std::vector<TValue>> &value) const
    {
      auto section = getSection(sectionName);

      if (section == nullptr)
	throw std::logic_error("Section '" + sectionName + "' not found");
      section->getArrayOfArray<TValue>(key, value);
    }

    std::string const get(std::string const &sectionName, std::string const &key);

    void set(std::string const &sectionName, std::string const &key, std::string const &value);

   private:
    bool isAComment(std::string const &line) const;
    bool isAEmptyLine(std::string const &line) const;
    bool isAStartingSection(std::string const &line, std::string &sectionName) const;
    void addNewSection(IniSection *section);
    bool parse(std::string const &currentLine);
    void checkLastLine(std::string &currentLine);

  };

}
#endif /* !_IniFileParser_H_ */
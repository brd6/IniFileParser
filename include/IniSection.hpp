//
// Created by brd6 on 01/04/17.
//

#ifndef _IniSection_H_
#define _IniSection_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

namespace ini
{
  const char DATA_SEPARATOR = '=';
  const char ARRAY_SEPARATOR = ',';
  const std::string COMMENT_SYMBOLS = "#;";
  const std::string SPACES_SYMBOL = " \t";
  const std::string DEFAULT_SECTION_NAME = "_";
  const std::string SECTION_DELIMITER = "[]";
  const std::string DATA_SEPARATORS = SPACES_SYMBOL + DATA_SEPARATOR;

  class IniSection
  {
   private:
    std::string mName;
    std::vector<std::string> mLines;
    std::unordered_map<std::string, std::string> mData;

   public:
    IniSection();
    IniSection(std::string const &name);
    IniSection(std::string const &name, std::vector<std::string> const &lines);
    IniSection(IniSection const &) = delete;
    IniSection &operator=(IniSection const &) = delete;
    virtual ~IniSection() = default;

    std::string const &getName() const;
    void setName(std::string const &name);
    void feed(std::string const &line);
    void parse();

    template<typename TValue>
    void get(std::string const &key, TValue &value) const
    {
      auto rawValue = get(key);

      value = convertValue<TValue>(rawValue);
    }

    template<typename TValue>
    void get(std::string const &key, std::vector<TValue> &value) const
    {
      auto rawValue = get(key);

      std::cout << "ok" << std::endl;

      //value = convertValueArray<TValue>(rawValue);
    }

    std::string const get(std::string const &key) const;

   private:
    std::string extractKey(std::string const &line) const;
    std::string extractValue(std::string const &line) const;
    bool isANewDataLine(std::string const &currentLine) const;

//    template <typename TValue>
//    std::vector<TValue> convertValueArray(std::string const &rawValue) const
//    {
//      std::string str;
//      std::istringstream iss(rawValue);
//
//      while (std::getline(iss, str, '\n'))
//	{
//	  std::cout << str << std::endl;
//	}
//    }

    template <typename TValue>
    TValue convertValue(std::string const &rawValue) const;
  };

  template <typename TValue>
  inline TValue IniSection::convertValue(std::string const &input) const
  {
      throw std::logic_error("Value type getter not implement yet.");
  }

  template<>
  inline int IniSection::convertValue<int>(std::string const &rawValue) const
  {
    int value;
    char c;

    std::stringstream ss(rawValue);
    ss >> value;
    if (ss.fail() || ss.get(c))
      throw std::logic_error("'" + rawValue + "' is not a int.");
    return value;
  }

  template<>
  inline double IniSection::convertValue<double>(std::string const &rawValue) const
  {
    double value;
    char c;

    std::stringstream ss(rawValue);
    ss >> value;
    if (ss.fail() || ss.get(c))
      throw std::logic_error("'" + rawValue + "' is not a double.");
    return value;
  }

  template<>
  inline float IniSection::convertValue<float>(std::string const &rawValue) const
  {
    float value;
    char c;

    std::stringstream ss(rawValue);
    ss >> value;
    if (ss.fail() || ss.get(c))
      throw std::logic_error("'" + rawValue + "' is not a float.");
    return value;
  }

  template<>
  inline short IniSection::convertValue<short>(std::string const &rawValue) const
  {
    short value;
    char c;

    std::stringstream ss(rawValue);
    ss >> value;
    if (ss.fail() || ss.get(c))
      throw std::logic_error("'" + rawValue + "' is not a short.");
    return value;
  }

  template<>
  inline bool IniSection::convertValue<bool>(std::string const &rawValue) const
  {
    bool value;

    std::istringstream(rawValue) >> value;
    return value;
  }

  template<>
  inline char IniSection::convertValue<char>(std::string const &rawValue) const
  {
    return rawValue.at(0);
  }

  template <>
  inline std::string IniSection::convertValue<std::string>(std::string const &rawValue) const
  {
    std::string value;

    value = rawValue;
    if (value.size() > 0 &&
	value.at(0) == '"' &&
	value.at(value.size() - 1) == '"')
      value = value.substr(1, value.size() - 2);
    return value;
  }

}

#endif /* !_IniSection_H_ */
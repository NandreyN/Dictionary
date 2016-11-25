#pragma once
#include <string>
#include <vector>

class DictionaryItem
{
public:
	explicit DictionaryItem(const std::string &key, const std::vector<std::string> &collection);
	bool removeTranslation(const std::string transl);
	bool addTranslation(const std::string tranls);
	bool isTranslationEmpty() const;
private:
	std::string _keyWord;
	std::vector<std::string> _translationCollection;
};


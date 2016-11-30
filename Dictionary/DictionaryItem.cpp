#include "DictionaryItem.h"
#include <algorithm>

DictionaryItem::DictionaryItem(const std::string& key, const std::vector<std::string>& collection)
{
	this->_keyWord = key;
	this->_translationCollection = collection;
}

bool DictionaryItem::removeTranslation(const std::string transl)
{
	try
	{
		this->_translationCollection.erase(std::remove(this->_translationCollection.begin(), this->_translationCollection.end(), transl), this->_translationCollection.end());
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool DictionaryItem::addTranslation(const std::string transl)
{
	try
	{
		this->_translationCollection.push_back(transl);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool DictionaryItem::isTranslationEmpty() const
{
	if (this->_keyWord.length() != 0 && this->_translationCollection.size() != 0)
		return false;
	return true;
}

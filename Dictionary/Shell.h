#pragma once
#include <string>
#include <map>
#include <vector>

#define AD "ad"
#define RM "rm"
#define SV "sv"
#define EX	"ex"
#define GT "gt"

struct Handler
{
	virtual bool execute(std::vector<std::string> params) = 0;

	virtual ~Handler()
	{
	}
};

class Shell
{
public:
	explicit Shell();
	~Shell();
	void Listen();
	static std::vector < std::string > splitString(const std::string& line);

private:
	std::map<std::string, Handler*> _handlers;
	std::map<std::string, std::string> _queueToAdd; // pair key - translation
	
	bool parseTranslation(const std::string& input);
	std::string getCommandFromInputStr(const std::string& input) const;
	bool executeCommand(const std::string& command);
	std::string toLower(std::string str) const;
};

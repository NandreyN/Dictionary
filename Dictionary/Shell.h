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

private:
	std::map<std::string, Handler*> _handlers;


	std::string getCommandFromInputStr(const std::string& input) const;
	bool executeCommand(const std::string& command);
	std::string toLower(std::string str) const;
};

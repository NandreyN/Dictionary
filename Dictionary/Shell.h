#pragma once
#include <string>
#include <map>

#define ADD "ad"
#define RM "rm"
#define SV "sv"
#define EX	"ex"

struct Handler
{
	virtual bool execute() = 0;
	virtual ~Handler() {}
};

class Shell
{
public:
	explicit Shell();
	~Shell();
	void Listen();

private:
	std::map<std::string, Handler*> _handlers;
	std::string getCommandFromInputStr(const std::string &input) const;
	bool executeCommand(const std::string &command);
	std::string toLower(std::string str) const;
};
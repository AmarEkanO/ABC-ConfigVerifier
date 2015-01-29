#include <string>
#include <regex>
#include "LeNameRule.h"

LeNameRule::LeNameRule()
{
	name = "";
	app = "";
}

bool LeNameRule::passes(string line)
{
	regex LeNameRx("^\\s*\\[\\s*App\\s*=\\s*(\\w{3})\\s*,\\s*Name\\s*=\\s*(\\w{6})\\s*\\]\\s*(;.*)?$",regex_constants::icase);
	smatch match;

	if(regex_search(line, match, LeNameRx))
	{
		name = match[2];
		app = match[1];
		return true;
	}
	else
	{
		name = "";
		app = "";
	}

	return false;
}

string LeNameRule::getApp() const
{
	return app;
}

string LeNameRule::getName() const
{
	return name;
}
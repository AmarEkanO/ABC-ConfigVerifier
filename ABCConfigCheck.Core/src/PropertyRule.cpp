#include<string>
#include<regex>
#include "PropertyRule.h"

PropertyRule::PropertyRule()
{
	name = "";
	value = "";
}

bool PropertyRule::passes(string line)
{
	regex LePropertyRx("^\\s*([^;=\\[]+)\\s*=\\s*\\b([^=;]*)\\s*(;.+)?$");
	smatch match;

	if(regex_search(line, match, LePropertyRx))
	{
		name = match[1];
		value = match[2];
		return true;
	}
	else
	{
		name = "";
		value = "";
	}

	return false;
}

string PropertyRule::getName() const
{
	return name;
}

string PropertyRule::getValue() const
{
	return value;
}
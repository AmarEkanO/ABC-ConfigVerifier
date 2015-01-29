#include <string>
#include <regex>
#include "WhitespaceRule.h"

bool WhitespaceRule::passes(string line)
{
	regex whiteSpaceRx("^\\s*$");
	if(regex_search(line, whiteSpaceRx))
		return true;
	
	return false;
}
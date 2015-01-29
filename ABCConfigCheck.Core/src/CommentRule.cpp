#include <string>
#include <regex>
#include "CommentRule.h"

bool CommentRule::passes(string line)
{
	regex commentRx("^\\s*;");
	if(regex_search(line, commentRx))
		return true;

	return false;
}
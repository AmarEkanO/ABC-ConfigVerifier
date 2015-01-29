#include "UtilityFunc.h"
#include <regex>

bool entryExists(vector<string> entries, string entry)
{
	for(vector<string>::iterator it = entries.begin(); it != entries.end(); it++)
		if(*it == entry)
			
			return true;

	return false;
}
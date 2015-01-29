#include "ErrorLog.h"

void ErrorLog::addMessage(int lineNumber, string message, string reason)
{
	string base = "Line " + to_string(lineNumber) + ": " + message;
	if(reason.empty())
		entries.push_back(base);
	else
		entries.push_back(base + " --> " + reason);
}

vector<string> ErrorLog::getEntries()
{
	return entries;
}

void ErrorLog::addMessages(ErrorLog log)
{
	vector<string> newEntries = log.getEntries();
	for(vector<string>::iterator it = newEntries.begin(); it != newEntries.end(); ++it)
	{
		entries.push_back(*it);
	}
}

ErrorLog::ErrorLog()
{
}

ErrorLog::~ErrorLog()
{
}
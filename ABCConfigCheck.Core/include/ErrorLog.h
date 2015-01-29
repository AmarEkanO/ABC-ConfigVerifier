#ifndef ERROR_LOG_H
#define ERROR_LOG_H

#include <vector>
#include <string>

using namespace std;

class ErrorLog
{
public:
	virtual void addMessage(int, string,string="");
	virtual void addMessages(ErrorLog);
	virtual vector<string> getEntries();
	virtual ~ErrorLog();
	explicit ErrorLog();

private:
	vector<string> entries;
};

#endif
#ifndef LE_NAME_RULE_H
#define LE_NAME_RULE_H

#include "IRule.h"

class LeNameRule : public IRule
{
public:
	virtual bool passes(string);
	virtual string getName() const;
	virtual string getApp() const;
	explicit LeNameRule();

private:
	string name;
	string app;
};

#endif
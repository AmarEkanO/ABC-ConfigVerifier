#ifndef PROPERTY_RULE_H
#define PROPERTY_RULE_H

#include "IRule.h"

class PropertyRule : public IRule
{
public:
	virtual bool passes(string);
	virtual string getName() const;
	virtual string getValue() const;
	explicit PropertyRule();

private:
	string name;
	string value;
};

#endif
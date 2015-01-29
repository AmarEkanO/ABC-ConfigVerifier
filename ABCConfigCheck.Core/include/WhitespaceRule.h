#ifndef WHITESPACE_RULE_H
#define WHITESPACE_RULE_H

#include "IRule.h"

class WhitespaceRule : public IRule
{
public:
	virtual bool passes(string);
};

#endif
#ifndef COMMENT_RULE_H
#define COMMENT_RULE_H

#include "IRule.h"

class CommentRule : public IRule
{
public:
	virtual bool passes(string);
};

#endif
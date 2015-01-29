#ifndef RULE_H
#define RULE_H

using namespace std;

class IRule
{
public:
	virtual bool passes(string) = 0;
};

#endif
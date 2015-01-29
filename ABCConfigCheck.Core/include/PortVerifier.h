#ifndef PORTVERIFIER_H
#define PORTVERIFIER_H

#include <vector>
#include "ConfigHandler.h"
#include "IVerifier.h"
#include "WhitespaceRule.h"
#include "CommentRule.h"
#include "PropertyRule.h"
#include "PortHeaderRule.h"
#include "ErrorLog.h"

class PortVerifier : public IVerifier
{
public:
	explicit PortVerifier(ConfigHandler&);
	virtual ~PortVerifier();
	virtual bool isValid();
	virtual vector<string> getInvalidEntries();

private:
	ConfigHandler &configHandle;
	ErrorLog invalidEntries;
};

#endif
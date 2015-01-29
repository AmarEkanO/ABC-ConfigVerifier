#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include "LE.h"
#include "LEInfo.h"
#include "ErrorLog.h"

using namespace std;

class IProtocol
{
public:
	virtual bool check(LE) = 0;
	virtual bool validate(LEInfo&) = 0;
	virtual ErrorLog getInvalidEntries() = 0;
};

#endif
#ifndef SEMANTIC_VERIFIER_H
#define SEMANTIC_VERIFIER_H

#include "IVerifier.h"
#include "LETable.h"
#include "ErrorLog.h"

class SemanticVerifier : public IVerifier
{
public:
	explicit SemanticVerifier(LETable&);
	virtual ~SemanticVerifier();
	virtual bool isValid();
	virtual vector<string> getInvalidEntries();

private:
	LETable& table;
	ErrorLog invalidEntries;
};

#endif
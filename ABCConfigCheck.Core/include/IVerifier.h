#ifndef VERIFIER_H
#define VERIFIER_H

#include <vector>

using namespace std;

class IVerifier
{
public:
	virtual bool isValid() = 0;
	virtual vector<string> getInvalidEntries() = 0;
};

#endif
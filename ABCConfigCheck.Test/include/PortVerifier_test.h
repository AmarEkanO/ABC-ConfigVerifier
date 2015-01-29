/* 
* Contains definition of mocked PortVerifier
*/
#ifndef PORT_VERIFIER_TEST_H
#define PORT_VERIFIER_TEST_H

#include "gmock\gmock.h"
#include "ConfigHandler_test.h"
#include "PortVerifier.h"

class MockPortVerifier : public PortVerifier
{
public:
	MockPortVerifier(ConfigHandler& handler): PortVerifier(handler){}
	MOCK_METHOD0(isValid, bool());
};

#endif
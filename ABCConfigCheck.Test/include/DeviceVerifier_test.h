/*
* Contains definition of mocked DeviceVerifier
*/
#ifndef DEVICE_VERIFIER_TEST_H
#define DEVICE_VERIFIER_TEST_H

#include "gmock\gmock.h"
#include "ConfigHandler_test.h"
#include "DeviceVerifier.h"

class MockDeviceVerifier : public DeviceVerifier
{
public:
	MockDeviceVerifier(ConfigHandler& handler):DeviceVerifier(handler){}
	MOCK_METHOD0(isValid, bool());
};

#endif
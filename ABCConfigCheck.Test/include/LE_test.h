/*
* Contains definition of mocked LE
*/
#ifndef LE_TEST_H
#define LE_TEST_H

#include "gmock\gmock.h"
#include "LE.h"

class MockLE : public LE
{
public:
	MOCK_CONST_METHOD0(hasName, bool());
	MOCK_CONST_METHOD0(getLeName, string());
	MOCK_METHOD2(setName, void(string app, string name));
	MOCK_CONST_METHOD0(propertyCount, int());
	MOCK_METHOD1(addProperty, void(Property prop));
	MOCK_METHOD0(clearProperties, void());
	MOCK_METHOD1(getProperty, Property(string prop));
	MOCK_METHOD1(getPropertyIndex, int(Property prop));
};

#endif
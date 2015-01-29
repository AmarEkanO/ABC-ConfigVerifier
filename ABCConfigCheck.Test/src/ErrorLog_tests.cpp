/*
** Contains test for ErrorLog
*/

#include "gtest\gtest.h"
#include "gmock\gmock.h"
#include "ErrorLog.h"
#include "UtilityFunc.h"

TEST(When_an_instance_is_created, there_should_be_no_messages)
{
	ErrorLog log;

	EXPECT_EQ(0,log.getEntries().size());
}

TEST(When_a_message_is_added, it_should_exist_in_the_entries)
{
	ErrorLog log;

	string message = "This is a test";
	int lineNumber = 10;

	log.addMessage(lineNumber, message);

	string expected_entry = "Line 10: This is a test";

	EXPECT_EQ(true, entryExists(log.getEntries(), expected_entry));
}

TEST(When_adding_a_message_and_reason, it_should_exist_in_the_entries)
{
	ErrorLog log;

	string message = "This is a test";
	string reason = "The reason being this is a test";
	int lineNumber = 10;

	log.addMessage(lineNumber, message, reason);

	string expected_entry = "Line 10: This is a test --> The reason being this is a test";

	EXPECT_EQ(true, entryExists(log.getEntries(), expected_entry));
}

TEST(Adding_an_instance_of_ErrorLog_to_messages, messages_should_get_appended_to_existing_messages)
{
	ErrorLog log1;
	
	const int size = 2;
	string message[size] = {"Message1 in Log1", "Message2 in Log1"};

	for(int i = 0; i < size; ++i)
		log1.addMessage(i+1, message[i]);

	ErrorLog log2;

	string message2 = "Message1 in Log2";
	log2.addMessage(1, message2);

	log1.addMessages(log2);

	string expected_string = "Line 1: " + message2;

	EXPECT_EQ(true, entryExists(log1.getEntries(), expected_string));
	EXPECT_EQ(size+1, log1.getEntries().size());
}
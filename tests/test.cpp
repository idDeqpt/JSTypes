#include <iostream>
#include <vector>
#include <string>
#include <JSTypes/JSTypes.hpp>


static int TEST_CASE_COUNTER = 0;
static int TEST_CASE_CHECKS_COUNTER = 0;
static int TEST_CASE_ERRORS_COUNTER = 0;

struct TestCaseGuard
{
	TestCaseGuard(const char* name)
	{
		TEST_CASE_COUNTER++;
		TEST_CASE_CHECKS_COUNTER = 0;
		TEST_CASE_ERRORS_COUNTER = 0;
		std::cout << "TEST CASE " << name << std::endl;
	}

	~TestCaseGuard()
	{
		if (TEST_CASE_ERRORS_COUNTER == 0)
			std::cout << "\tPASSED\n";
		else
			std::cout << "\tFAILED (" << TEST_CASE_ERRORS_COUNTER
					  << " error(s), " << TEST_CASE_CHECKS_COUNTER << " checks)\n";
	}
};

#define TEST_CASE(x) if (TestCaseGuard __tc_guard{x}; true)
#define CHECK(x, y)\
TEST_CASE_CHECKS_COUNTER++;\
if (!(x == y)) { TEST_CASE_ERRORS_COUNTER++;\
std::cout << "\tCHECK FAILED\n\t\tIN   : " << x << "\n\t\tNEED : " << y << std::endl; }


std::ostream& operator<<(std::ostream& is, const jst::JSONParseError& er)
{
    return is << er.getPosition() << " " << er.getType();
}


int main()
{
	TEST_CASE("JSBool")
	{
		jst::JSBoolean v;
		CHECK(v.toString(), "null");
		
		jst::JSBoolean v1(false);
		CHECK(v1.toString(), "false");
	}

	TEST_CASE("JSNumber")
	{
		jst::JSNumber v;
		CHECK(v.toString(), "null");
		
		jst::JSNumber v1(7);
		CHECK(v1.toString(), "7.000000");
		
		jst::JSNumber v2;
		v2 = 78;
		CHECK(v2.toString(), "78.000000");
	}

	TEST_CASE("JSString")
	{
		jst::JSString v;
		CHECK(v.toString(), "null");
		
		jst::JSString v1(13);
		CHECK(v1.toString(), "\"13.000000\"");
		
		jst::JSString v2("stddy");
		CHECK(v2.toString(), "\"stddy\"");
		
		jst::JSString v3;
		v3 = "dsljf";
		CHECK(v3.toString(), "\"dsljf\"");
	}

	TEST_CASE("JSObject")
	{
		jst::JSObject v;
		CHECK(v.toString(), "null");
		
		jst::JSObject v1;
		v1.addField("key1");
		v1.addField("key2", std::make_shared<jst::JSBoolean>(true));
		v1.addField("key3", std::make_shared<jst::JSNumber>(34));
		v1.addField("key4", std::make_shared<jst::JSString>("abbebe"));
		v1.addField("key5", std::make_shared<jst::JSNumber>());
		CHECK(v1.toString(), "{\"key1\":null,\"key2\":true,\"key3\":34.000000,\"key4\":\"abbebe\",\"key5\":null}");
		
		jst::JSObject v2;
		v2.addField("key2", std::make_shared<jst::JSNumber>(304));
		v2.addField("key3", std::make_shared<jst::JSNumber>(34));
		v2.removeField("key3");
		CHECK(v2.toString(), "{\"key2\":304.000000}");
		
		jst::JSObject v3;
		v3.addField("key1", std::make_shared<jst::JSObject>(v1));
		v3.addField("key2", std::make_shared<jst::JSObject>(v2));
		CHECK(v3.toString(), "{\"key1\":{\"key1\":null,\"key2\":true,\"key3\":34.000000,\"key4\":\"abbebe\",\"key5\":null},\"key2\":{\"key2\":304.000000}}");
	}

	TEST_CASE("JSArray")
	{
		jst::JSObject obj1;
		obj1.addField("key1");
		obj1.addField("key2", std::make_shared<jst::JSBoolean>(true));
		obj1.addField("key3", std::make_shared<jst::JSNumber>(34));
		obj1.addField("key4", std::make_shared<jst::JSString>("abbebe"));
		obj1.addField("key5", std::make_shared<jst::JSNumber>());

		jst::JSArray v;
		CHECK(v.toString(), "null");

		jst::JSArray v1;
		v1.pushBack(std::make_shared<jst::JSUndefined>());
		v1.pushBack(std::make_shared<jst::JSNumber>());
		v1.pushBack(std::make_shared<jst::JSNumber>(45));
		v1.pushBack(std::make_shared<jst::JSObject>(obj1));
		CHECK(v1.toString(), "[null,null,45.000000,{\"key1\":null,\"key2\":true,\"key3\":34.000000,\"key4\":\"abbebe\",\"key5\":null}]");

		jst::JSArray v2;
		v2.pushBack(std::make_shared<jst::JSNumber>(45));
		v2.pushBack(std::make_shared<jst::JSNumber>(405));
		v2.pushBack(std::make_shared<jst::JSNumber>(45));
		v2.popBack();
		CHECK(v2.toString(), "[45.000000,405.000000]");

		jst::JSArray v3;
		v3.pushBack(std::make_shared<jst::JSArray>(v2));
		v3.pushBack(std::make_shared<jst::JSArray>(v3));
		v3.popBack();
		CHECK(v3.toString(), "[[45.000000,405.000000]]");
	}

	TEST_CASE("Parsing")
	{
		struct ParseEntry
		{
			const char* line;
			jst::JSONParseError expected_error;
		};

		std::vector<ParseEntry> json_strings = {
			{"",        jst::JSONParseError(0, jst::JSONParseError::ErrorType::EMPTY_FILE)},
			{"rpkegij", jst::JSONParseError(0, jst::JSONParseError::ErrorType::UNEXPECTED_CHARACTER)},
			{"true",    jst::JSONParseError()},
			{"false",   jst::JSONParseError()},
			{"-",       jst::JSONParseError(0, jst::JSONParseError::ErrorType::INCORRECT_NUMBER)},
			{"1",       jst::JSONParseError()},
			{"13",      jst::JSONParseError()},
			{"13.75   ",  jst::JSONParseError()},
			{"1a3.75   ", jst::JSONParseError()},
			{"-13.75",    jst::JSONParseError()},
			{"-13.7.5",   jst::JSONParseError(0, jst::JSONParseError::ErrorType::INCORRECT_NUMBER)},
			{"\"string ex\\\"ample\"", jst::JSONParseError()},
			{"\"bad string example",   jst::JSONParseError(0, jst::JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET)},
			{"[]",   jst::JSONParseError()},
			{"[42]", jst::JSONParseError()},
			{"[true,23,\"string into array\"]",      jst::JSONParseError()},
			{"[true,23,\"bad string into array]",    jst::JSONParseError(9, jst::JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET)},
			{"[true,23,\"bad string into bad array", jst::JSONParseError(9, jst::JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET)},
			{"[true,23,\"bad array example\"",       jst::JSONParseError(0, jst::JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET)},
			{"[true,23,\"bad array example\", [13]", jst::JSONParseError(0, jst::JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET)},
			{"[true,23,\"bad array example\", [13, [true, 1]], false]", jst::JSONParseError()},
			{"{}", jst::JSONParseError()},
			{"{\"key1\": true, \"key2\": 13, \"key3\": \"string into object\"}", jst::JSONParseError()},
			{"{\"key3\": \"string into object\", \"key1\": [false, 43]}",        jst::JSONParseError()},
			{"{\"key1\": true, \"key2\": 13, \"key3\": \"string into object\", [false, 43, {\"abc\": 32}]}",                jst::JSONParseError(57, jst::JSONParseError::ErrorType::INCORRECT_OBJECT_KEY_NAME)},
			{"{\"key1\": true, \"key2\": 13, \"key3\": \"string into object\", \"big_key\": \n[false, 43, {\"abc\": 32}]}", jst::JSONParseError()},
		};
		jst::JSON json;
		for (unsigned int i = 0; i < json_strings.size(); i++)
		{
			json.parse(json_strings[i].line);
			CHECK(json.getErrorData(), json_strings[i].expected_error);
		}
	}

	system("pause");
	return 0;
}
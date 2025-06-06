#include "JSTypes/JSString.hpp"

#include <string>


jst::JSString::JSString()
{
	undefined = true;
}

jst::JSString::JSString(float value)
{
	undefined = false;
	this->value = std::to_string(value);
}

jst::JSString::JSString(std::string value)
{
	undefined = false;
	this->value = value;
}


std::string jst::JSString::getString()
{
	return value;
}


std::string jst::JSString::toString()
{
	return (undefined) ? "undefined" : ("\"" + value + "\"");
}


void jst::JSString::operator=(std::string new_value)
{
	undefined = false;
	value = new_value;
}
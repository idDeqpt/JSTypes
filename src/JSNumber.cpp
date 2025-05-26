#include "JSTypes/JSNumber.hpp"

#include <string>


jst::JSNumber::JSNumber()
{
	undefined = true;
}

jst::JSNumber::JSNumber(float value)
{
	undefined = false;
	this->value = value;
}


std::string jst::JSNumber::toString()
{
	return (undefined) ? "undefined" : std::to_string(value);
}


void jst::JSNumber::operator=(float new_value)
{
	undefined = false;
	value = new_value;
}

jst::JSNumber::operator float() const
{
	return value;
}
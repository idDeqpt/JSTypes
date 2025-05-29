#include "JSTypes/JSBoolean.hpp"

#include <string>


jst::JSBoolean::JSBoolean()
{
	undefined = true;
}

jst::JSBoolean::JSBoolean(bool value)
{
	undefined = false;
	this->value = value;
}


std::string jst::JSBoolean::toString()
{
	return (undefined) ? "undefined" : (value ? "true" : "false");
}


void jst::JSBoolean::operator=(bool new_value)
{
	undefined = false;
	value = new_value;
}

jst::JSBoolean::operator bool() const
{
	return value;
}
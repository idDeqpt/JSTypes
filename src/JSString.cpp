#include <JSTypes/JSString.hpp>

#include <string>


namespace jst
{

JSString::JSString(float value):
	m_value(std::to_string(value))
{
	m_undefined = false;
}

JSString::JSString(std::string value):
	m_value(value)
{
	m_undefined = false;
}


const std::string& JSString::getString() const
{
	return m_value;
}


std::string JSString::toString() const
{
	return (m_undefined) ? "null" : ("\"" + m_value + "\"");
}


void JSString::operator=(const std::string& new_value)
{
	m_undefined = false;
	m_value = new_value;
}

} //namespace jst
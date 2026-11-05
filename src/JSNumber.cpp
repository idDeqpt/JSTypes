#include <JSTypes/JSNumber.hpp>

#include <string>

namespace jst
{

JSNumber::JSNumber(float value):
	m_value(value)
{
	m_undefined = false;
}


std::string JSNumber::toString() const
{
	return (m_undefined) ? "null" : std::to_string(m_value);
}


void JSNumber::operator=(float new_value)
{
	m_undefined = false;
	m_value = new_value;
}

JSNumber::operator float() const
{
	return m_value;
}

} //namespace jst
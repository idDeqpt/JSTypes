#include <JSTypes/JSBoolean.hpp>

#include <string>

namespace jst
{

JSBoolean::JSBoolean(bool value):
	m_value(value)
{
	m_undefined = false;
}


std::string JSBoolean::toString() const
{
	return (m_undefined) ? "null" : (m_value ? "true" : "false");
}


void JSBoolean::operator=(bool new_value)
{
	m_undefined = false;
	m_value = new_value;
}

JSBoolean::operator bool() const
{
	return m_value;
}

} //namespace jst
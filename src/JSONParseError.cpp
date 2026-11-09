#include "JSTypes/JSONParseError.hpp"


jst::JSONParseError::JSONParseError()
{
	m_position = -1;
	m_type = ErrorType::NO_ERROR;
}

jst::JSONParseError::JSONParseError(int position, ErrorType type)
{
	m_position = position;
	m_type = type;
}


int jst::JSONParseError::getPosition() const
{
	return m_position;
}

jst::JSONParseError::ErrorType jst::JSONParseError::getType() const
{
	return m_type;
}


bool jst::JSONParseError::operator==(const JSONParseError& other) const
{
	return ((m_type == other.m_type) && (m_position == other.m_position));
}
#include "JSTypes/JSONParseError.hpp"


jst::JSONParseError::JSONParseError()
{
	position = -1;
	type = ErrorType::NO_ERROR;
}

jst::JSONParseError::JSONParseError(int position, ErrorType type)
{
	this->position = position;
	this->type = type;
}


int jst::JSONParseError::getPosition()
{
	return position;
}

jst::JSONParseError::ErrorType jst::JSONParseError::getType()
{
	return type;
}
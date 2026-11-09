#ifndef JSON_PARSE_ERROR_TYPE_HPP
#define JSON_PARSE_ERROR_TYPE_HPP

namespace jst
{
	class JSONParseError
	{
	public:
		enum ErrorType
		{
			NO_ERROR,
			EMPTY_FILE,
			UNEXPECTED_CHARACTER,
			EXPECTED_CLOSING_BRACKET,
			INCORRECT_NUMBER,
			INCORRECT_OBJECT_KEY_NAME,
		};
		
		JSONParseError();
		JSONParseError(int position, ErrorType error_type);

		int getPosition() const;
		ErrorType getType() const;

		bool operator==(const JSONParseError& other) const;

	protected:
		int m_position;
		ErrorType m_type;
	};
}

#endif //JSON_PARSE_ERROR_TYPE_HPP
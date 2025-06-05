#ifndef JSON_PARSER_CLASS_HPP
#define JSON_PARSER_CLASS_HPP

#include <string>
#include <memory>

#include "JSBaseType.hpp"
#include "JSONParseError.hpp"


namespace jst
{
	class JSON
	{
	public:
		JSON();

		bool parse(std::string& json);

		std::shared_ptr<JSBaseType> getParseResult();
		JSONParseError getErrorData();

	protected:
		std::string* json_ptr;
		int cur_pos;
		bool string_over;
		JSONParseError last_error;
		std::shared_ptr<JSBaseType> parse_result;

		void peek();
		void peekTo(int new_pos);
		void skip_whitespaces();

		std::shared_ptr<JSBaseType> parse_process();

		std::shared_ptr<JSBaseType> parse_bool();
		std::shared_ptr<JSBaseType> parse_number();
		std::string parse_string();
		std::shared_ptr<JSBaseType> parse_array();
		std::shared_ptr<JSBaseType> parse_object();
	};
}

#endif //JSON_PARSER_CLASS_HPP
#ifndef JSON_PARSER_CLASS_HPP
#define JSON_PARSER_CLASS_HPP

#include <string>
#include <memory>

#include <JSTypes/JSBaseType.hpp>
#include <JSTypes/JSONParseError.hpp>

namespace jst
{
	class JSON
	{
	public:
		JSON();

		bool parse(const std::string& json);

		std::shared_ptr<JSBaseType> getParseResult();
		JSONParseError getErrorData() const;

	protected:
		const std::string* json_ptr;
		int cur_pos;
		bool string_over;
		JSONParseError last_error;
		std::shared_ptr<JSBaseType> parse_result;

		void peek();
		void peekTo(int new_pos);
		void skip_whitespaces();

		std::shared_ptr<JSBaseType> parse_process();

		std::shared_ptr<JSBaseType> try_parse_null();
		std::shared_ptr<JSBaseType> try_parse_bool();
		std::shared_ptr<JSBaseType> try_parse_number();
		std::shared_ptr<JSBaseType> try_parse_string();
		std::shared_ptr<JSBaseType> try_parse_array();
		std::shared_ptr<JSBaseType> try_parse_object();
	};
}

#endif //JSON_PARSER_CLASS_HPP
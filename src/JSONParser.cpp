#include <JSTypes/JSONParser.hpp>

#include <JSTypes/JSTypes.hpp>
#include <JSTypes/JSONParseError.hpp>

#include <string>
#include <memory>

namespace jst
{

jst::JSON::JSON()
{
	string_over = false;
	cur_pos = 0;
	parse_result = std::make_shared<JSUndefined>();
	last_error = JSONParseError();
}


bool jst::JSON::parse(const std::string& json)
{
	if (json.size() == 0)
	{
		last_error = JSONParseError(0, JSONParseError::ErrorType::EMPTY_FILE);
		return false;
	}

	string_over = false;
	cur_pos = 0;
	json_ptr = &json;
	last_error = JSONParseError();
	parse_result = parse_process();
	return (last_error.getType() == JSONParseError::ErrorType::NO_ERROR);
}


std::shared_ptr<jst::JSBaseType> jst::JSON::getParseResult()
{
	return parse_result;
}

jst::JSONParseError jst::JSON::getErrorData() const
{
	return last_error;
}


void jst::JSON::peek()
{
	if (cur_pos >= (json_ptr->size() - 1))
	{
		string_over = true;
		return;
	}

	cur_pos++;
	string_over = false;
}

void jst::JSON::peekTo(int new_pos)
{
	cur_pos = new_pos;
}

void jst::JSON::skip_whitespaces()
{
	while ((json_ptr->at(cur_pos) == ' ') || (json_ptr->at(cur_pos) == '\n'))
		peek();
}


std::shared_ptr<jst::JSBaseType> jst::JSON::parse_process()
{
	if (last_error.getType() != JSONParseError::ErrorType::NO_ERROR)
		return std::shared_ptr<JSBaseType>();

	skip_whitespaces();

	// if number
	if (auto res = try_parse_number(); res != nullptr)
		return res;

	// if string
	if (auto res = try_parse_string(); res != nullptr)
		return res;

	// if array
	if (auto res = try_parse_array(); res != nullptr)
		return res;

	// if object
	if (auto res = try_parse_object(); res != nullptr)
		return res;

	// if bool
	if (auto res = try_parse_bool(); res != nullptr)
		return res;

	// if null
	if (auto res = try_parse_null(); res != nullptr)
		return res;

	if (last_error.getType() == JSONParseError::ErrorType::NO_ERROR)
		last_error = JSONParseError(cur_pos, JSONParseError::ErrorType::UNEXPECTED_CHARACTER);

	return std::shared_ptr<JSBaseType>(nullptr);
}


std::shared_ptr<jst::JSBaseType> jst::JSON::try_parse_null()
{
    skip_whitespaces();
    if (json_ptr->substr(cur_pos, 4) == "null")
    {
        peek();peek();peek();peek();
        return std::make_shared<JSUndefined>();
    }
    return std::shared_ptr<JSBaseType>(nullptr);
}

std::shared_ptr<jst::JSBaseType> jst::JSON::try_parse_bool()
{
	skip_whitespaces();
	if (json_ptr->substr(cur_pos, 4) == "true")
	{
		peek();peek();peek();peek();
		return std::make_shared<JSBoolean>(true);
	}
	else if (json_ptr->substr(cur_pos, 5) == "false")
	{
		peek();peek();peek();peek();peek();
		return std::make_shared<JSBoolean>(false);
	}
	return std::shared_ptr<JSBaseType>(nullptr);
}

std::shared_ptr<jst::JSBaseType> jst::JSON::try_parse_number()
{
	skip_whitespaces();
	if ((json_ptr->at(cur_pos) != '-') && !((json_ptr->at(cur_pos) > 47) && (json_ptr->at(cur_pos) < 58)))
		return std::shared_ptr<JSBaseType>(nullptr);

	int start_pos = cur_pos;
	peek();

	while (!string_over && ((json_ptr->at(cur_pos) == '.') || ((json_ptr->at(cur_pos) > 47) && (json_ptr->at(cur_pos) < 58))))
		peek();

	int points_count = 0;
	for (unsigned int i = start_pos; i < cur_pos; i++)
		if (json_ptr->at(i) == '.')
			points_count++;

	if (points_count < 2)
		try
		{
			return std::make_shared<JSNumber>(stof(json_ptr->substr(start_pos, ((string_over) ? cur_pos + 1 : cur_pos) - start_pos)));
		} catch(...) {}

	if (last_error.getType() == JSONParseError::ErrorType::NO_ERROR)
		last_error = JSONParseError(start_pos, JSONParseError::ErrorType::INCORRECT_NUMBER);
	return std::shared_ptr<JSBaseType>(nullptr);
}

std::shared_ptr<jst::JSBaseType> jst::JSON::try_parse_string()
{
	skip_whitespaces();
	if (json_ptr->at(cur_pos) != '"')
		return std::shared_ptr<JSBaseType>(nullptr);

	skip_whitespaces();
	peek();

	int start_pos = cur_pos;
	while (json_ptr->at(cur_pos) != '"')
	{
		if (string_over)
		{
			if (last_error.getType() == JSONParseError::ErrorType::NO_ERROR)
				last_error = JSONParseError(start_pos - 1, JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET);
			return std::shared_ptr<JSBaseType>(nullptr);
		}

		if (json_ptr->at(cur_pos) == '\\')
			peek();
		peek();
	}
	peek();
	return std::make_shared<JSString>(json_ptr->substr(start_pos, ((string_over) ? cur_pos : cur_pos - 1) - start_pos));
}

std::shared_ptr<jst::JSBaseType> jst::JSON::try_parse_array()
{
	skip_whitespaces();
	if (json_ptr->at(cur_pos) != '[')
		return std::shared_ptr<JSBaseType>(nullptr);

	int start_pos = cur_pos;
	JSArray result;
	peek();
	skip_whitespaces();

	if (json_ptr->at(cur_pos) == ']')
	{
		peek();
		return std::make_shared<JSArray>(result);
	}

	int brackets_counter;
	for (brackets_counter = 1; !string_over && (brackets_counter != 0); )
	{
		std::shared_ptr<JSBaseType> el = parse_process();
		if (el != nullptr)
		{
			result.pushBack(el);
			if (string_over)
				break;
		}

		skip_whitespaces();

		if (json_ptr->at(cur_pos) == ']')
		{
			brackets_counter--; 
			break;
		}
		peek();
	}
	peek();

	if (brackets_counter > 0)
	{
		if (last_error.getType() == JSONParseError::ErrorType::NO_ERROR)
			last_error = JSONParseError(start_pos, JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET);
		return std::shared_ptr<JSBaseType>(nullptr);
	}
	return std::make_shared<JSArray>(result);
}

std::shared_ptr<jst::JSBaseType> jst::JSON::try_parse_object()
{
	skip_whitespaces();
	if (json_ptr->at(cur_pos) != '{')
		return std::shared_ptr<JSBaseType>(nullptr);

	int start_pos = cur_pos;
	JSObject result;
	peek();
	skip_whitespaces();

	if (json_ptr->at(cur_pos) == '}')
	{
		peek();
		return std::make_shared<JSObject>(result);
	}

	int brackets_counter;
	for (brackets_counter = 1; !string_over && (brackets_counter != 0); )
	{
		auto key_name = try_parse_string();
		if ((key_name == nullptr) || (static_cast<JSString*>(key_name.get())->getString() == ""))
		{
			if (last_error.getType() == JSONParseError::ErrorType::NO_ERROR)
				last_error = JSONParseError(cur_pos, JSONParseError::ErrorType::INCORRECT_OBJECT_KEY_NAME);
			return std::shared_ptr<JSBaseType>(nullptr);
		}
		peek();

		std::shared_ptr<JSBaseType> el = parse_process();
		if (el != nullptr)
			result.addField(static_cast<JSString*>(key_name.get())->getString(), el);
		else
		{
			if (last_error.getType() == JSONParseError::ErrorType::NO_ERROR)
				last_error = JSONParseError(cur_pos, JSONParseError::ErrorType::UNEXPECTED_CHARACTER);
			return std::shared_ptr<JSBaseType>(nullptr);
		}

		skip_whitespaces();

		if (json_ptr->at(cur_pos) == '}')
		{
			brackets_counter--; 
			break;
		}
		peek();
	}
	peek();

	if (brackets_counter > 0)
	{
		if (last_error.getType() == JSONParseError::ErrorType::NO_ERROR)
			last_error = JSONParseError(start_pos, JSONParseError::ErrorType::EXPECTED_CLOSING_BRACKET);
		return std::shared_ptr<JSBaseType>(nullptr);
	}
	return std::make_shared<JSObject>(result);
}

} //namespace jst
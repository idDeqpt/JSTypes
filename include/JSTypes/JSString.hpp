#ifndef JS_STRING_TYPE_HPP
#define JS_STRING_TYPE_HPP

#include <JSTypes/JSBaseType.hpp>
#include <string>

namespace jst
{
	class JSString : public JSBaseType
	{
	public:
		JSString() = default;
		JSString(float value);
		JSString(std::string value);

		const std::string& getString() const;

		std::string toString() const override;

		void operator=(const std::string& new_value);

	protected:
		std::string m_value = "";
	};
}

#endif //JS_STRING_TYPE_HPP
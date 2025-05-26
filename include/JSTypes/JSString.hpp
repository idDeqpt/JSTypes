#ifndef JS_STRING_TYPE_HPP
#define JS_STRING_TYPE_HPP

#include <string>
#include "JSBaseType.hpp"


namespace jst
{
	class JSString : public JSBaseType
	{
	public:
		JSString();
		JSString(float value);
		JSString(std::string value);

		std::string toString() override;

		void operator=(std::string new_value);

	protected:
		std::string value;
	};
}

#endif //JS_STRING_TYPE_HPP
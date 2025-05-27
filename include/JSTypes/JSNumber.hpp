#ifndef JS_NUMBER_TYPE_HPP
#define JS_NUMBER_TYPE_HPP

#include "JSBaseType.hpp"
#include <iostream>


namespace jst
{
	class JSNumber : public JSBaseType
	{
	public:
		JSNumber();
		JSNumber(float value);

		std::string toString() override;
		void destroy() override {}

		void operator=(float new_value);
		operator float() const;

	protected:
		float value;
	};
}

#endif //JS_NUMBER_TYPE_HPP
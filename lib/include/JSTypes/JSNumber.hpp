#ifndef JS_NUMBER_TYPE_HPP
#define JS_NUMBER_TYPE_HPP

#include "JSBaseType.hpp"


namespace jst
{
	class JSNumber : public JSBaseType
	{
	public:
		JSNumber();
		JSNumber(float value);

	protected:
		float value;
	};
}

#endif //JS_NUMBER_TYPE_HPP
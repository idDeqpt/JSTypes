#ifndef JS_UNDEFINED_TYPE_HPP
#define JS_UNDEFINED_TYPE_HPP

#include <JSTypes/JSBaseType.hpp>

namespace jst
{
	class JSUndefined : public JSBaseType
	{
	public:
		std::string toString() const override { return "null"; }
	};
}

#endif // JS_UNDEFINED_TYPE_HPP
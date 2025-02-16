#ifndef JS_OBJECT_HPP
#define JS_OBJECT_HPP

#include <string>


namespace jst
{
	class JSObject
	{
	public:
		virtual std::string toString();
	};
}

#endif //JS_OBJECT_HPP
#ifndef JS_BASE_TYPE_HPP
#define JS_BASE_TYPE_HPP

#include <string>


namespace jst
{
	class JSBaseType
	{
	public:
		bool undefined;
		virtual std::string toString();
	};
}

#endif //JS_BASE_TYPE_HPP
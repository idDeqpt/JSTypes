#ifndef JS_BASE_TYPE_HPP
#define JS_BASE_TYPE_HPP

#include <string>


namespace jst
{
	class JSBaseType
	{
	public:
		JSBaseType() {undefined = true;}
		bool undefined;
		virtual std::string toString() {return "JSBaseType";}
		virtual void destroy() {}
	};
}

#endif //JS_BASE_TYPE_HPP
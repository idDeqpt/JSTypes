#ifndef JS_BASE_TYPE_HPP
#define JS_BASE_TYPE_HPP

#include <string>

namespace jst
{
	class JSBaseType
	{
	public:
		JSBaseType() = default;
		virtual ~JSBaseType() = default;

		virtual std::string toString() const = 0;
		virtual void destroy() {m_undefined = true;}

		bool isUndefined() const {return m_undefined;}

	protected:
		bool m_undefined = true;
	};
}

#endif //JS_BASE_TYPE_HPP
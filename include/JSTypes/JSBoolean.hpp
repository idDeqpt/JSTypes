#ifndef JS_BOOLEAN_TYPE_HPP
#define JS_BOOLEAN_TYPE_HPP

#include <JSTypes/JSBaseType.hpp>

namespace jst
{
	class JSBoolean : public JSBaseType
	{
	public:
		JSBoolean() = default;
		JSBoolean(bool value);

		std::string toString() const override;

		void operator=(bool new_value);
		operator bool() const;

	protected:
		bool m_value = 0;
	};
}

#endif //JS_BOOLEAN_TYPE_HPP
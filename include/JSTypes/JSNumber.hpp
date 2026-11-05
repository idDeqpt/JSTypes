#ifndef JS_NUMBER_TYPE_HPP
#define JS_NUMBER_TYPE_HPP

#include <JSTypes/JSBaseType.hpp>

namespace jst
{
	class JSNumber : public JSBaseType
	{
	public:
		JSNumber() = default;
		JSNumber(float value);

		std::string toString() const override;

		void operator=(float new_value);
		operator float() const;

	protected:
		float m_value = 0;
	};
}

#endif //JS_NUMBER_TYPE_HPP
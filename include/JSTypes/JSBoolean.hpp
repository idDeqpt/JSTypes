#ifndef JS_BOOLEAN_TYPE_HPP
#define JS_BOOLEAN_TYPE_HPP

#include "JSBaseType.hpp"


namespace jst
{
	class JSBoolean : public JSBaseType
	{
	public:
		JSBoolean();
		JSBoolean(bool value);

		std::string toString() override;

		void operator=(bool new_value);
		operator bool() const;

	protected:
		bool value;
	};
}

#endif //JS_BOOLEAN_TYPE_HPP
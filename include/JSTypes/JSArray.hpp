#ifndef JS_ARRAY_TYPE_HPP
#define JS_ARRAY_TYPE_HPP

#include <vector>
#include <string>
#include <memory>

#include "JSBaseType.hpp"


namespace jst
{
	class JSArray : public JSBaseType
	{
	public:
		JSArray();
		~JSArray();

		void pushBack(std::shared_ptr<JSBaseType> new_value_ptr);
		void popBack();
		std::shared_ptr<JSBaseType>& back();
		unsigned int size();

		std::string toString() override;
		void destroy() override;

		std::shared_ptr<JSBaseType>&  operator[](unsigned int index);

	protected:
		std::vector<std::shared_ptr<JSBaseType>> values;
	};
}

#endif //JS_ARRAY_TYPE_HPP
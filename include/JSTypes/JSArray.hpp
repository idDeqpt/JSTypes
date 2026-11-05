#ifndef JS_ARRAY_TYPE_HPP
#define JS_ARRAY_TYPE_HPP

#include <vector>
#include <string>
#include <memory>

#include <JSTypes/JSBaseType.hpp>


namespace jst
{
	class JSArray : public JSBaseType
	{
	public:
		JSArray() = default;
		~JSArray();

		void pushBack(std::shared_ptr<JSBaseType> new_value_ptr);
		void popBack();

		std::shared_ptr<JSBaseType>& back();
		unsigned int size() const;

		std::string toString() const override;
		void destroy() override;

		std::shared_ptr<JSBaseType>&  operator[](unsigned int index);

	protected:
		std::vector<std::shared_ptr<JSBaseType>> m_values;
	};
}

#endif //JS_ARRAY_TYPE_HPP
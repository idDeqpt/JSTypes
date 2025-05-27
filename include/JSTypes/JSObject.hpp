#ifndef JS_OBJECT_TYPE_HPP
#define JS_OBJECT_TYPE_HPP

#include <utility>
#include <vector>
#include <string>
#include <memory>

#include "JSBaseType.hpp"


namespace jst
{
	class JSObject : public JSBaseType
	{
	public:
		JSObject();
		~JSObject();

		bool addField(std::string key);
		bool addField(std::string key, std::shared_ptr<JSBaseType> value_ptr);
		bool removeField(std::string key);

		std::string toString() override;
		void destroy() override;

		std::shared_ptr<JSBaseType>& operator[](std::string key);

	protected:
		std::vector<std::pair<std::string, std::shared_ptr<JSBaseType>>> fields;
	};
}

#endif //JS_OBJECT_TYPE_HPP
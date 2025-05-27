#ifndef JS_OBJECT_TYPE_HPP
#define JS_OBJECT_TYPE_HPP

#include <utility>
#include <vector>
#include <string>

#include "JSBaseType.hpp"


namespace jst
{
	class JSObject : public JSBaseType
	{
	public:
		JSObject();
		~JSObject();

		bool addField(std::string key);
		bool removeField(std::string key);

		std::string toString() override;
		void destroy() override;

		JSBaseType*& operator[](std::string key);

	protected:
		std::vector<std::pair<std::string, JSBaseType*>> fields;
	};
}

#endif //JS_OBJECT_TYPE_HPP
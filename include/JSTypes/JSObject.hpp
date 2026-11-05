#ifndef JS_OBJECT_TYPE_HPP
#define JS_OBJECT_TYPE_HPP

#include <utility>
#include <vector>
#include <string>
#include <memory>

#include <JSTypes/JSBaseType.hpp>

namespace jst
{
	class JSObject : public JSBaseType
	{
	public:
		JSObject() = default;
		~JSObject();

		bool addField(std::string key);
		bool addField(std::string key, std::shared_ptr<JSBaseType> value_ptr);
		bool removeField(std::string key);

		std::string toString() const override;
		void destroy() override;

		std::shared_ptr<JSBaseType>& operator[](const std::string& key);

	protected:
		std::vector<std::pair<std::string, std::shared_ptr<JSBaseType>>> m_fields;
		static std::shared_ptr<JSBaseType> s_null_element;
	};
}

#endif //JS_OBJECT_TYPE_HPP
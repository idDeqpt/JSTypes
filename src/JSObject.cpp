#include "JSTypes/JSObject.hpp"

#include <utility>
#include <string>
#include <memory>


jst::JSObject::JSObject()
{
	undefined = true;
	fields.clear();
}

jst::JSObject::~JSObject()
{
	destroy();
}


bool jst::JSObject::addField(std::string key)
{
	for (unsigned int i = 0; i < fields.size(); i++)
		if (fields[i].first == key)
			return false;

	fields.push_back(std::make_pair(key, std::make_shared<JSBaseType>()));
	return true;
}

bool jst::JSObject::addField(std::string key, std::shared_ptr<JSBaseType> value_ptr)
{
	for (unsigned int i = 0; i < fields.size(); i++)
		if (fields[i].first == key) 
			return false;

	fields.push_back(std::make_pair(key, value_ptr));
	return true;
}

bool jst::JSObject::removeField(std::string key)
{
	for (unsigned int i = 0; i < fields.size(); i++)
		if (fields[i].first == key)
		{
			if (fields[i].second.get() != this)
				fields[i].second->destroy();
			fields.erase(fields.begin() + i);
			return true;
		}
	return false;
}


std::string jst::JSObject::toString()
{
	if (fields.size() > 0)
		undefined = false;

	if (undefined)
		return "null";

	std::string result = "{";
	for (unsigned int i = 0; i < fields.size(); i++)
		result += "\"" + fields[i].first + "\":" + ((fields[i].second.get() == this) ? "null" : fields[i].second->toString()) + ",";

	if (fields.size() > 0)
		result.pop_back();
	result += "}";
	return result;
}

void jst::JSObject::destroy()
{
	fields.clear();
	undefined = true;
}


std::shared_ptr<jst::JSBaseType>& jst::JSObject::operator[](std::string key)
{
	for (unsigned int i = 0; i < fields.size(); i++)
		if (key == fields[i].first)
			return fields[i].second;
	return std::shared_ptr<JSBaseType>(nullptr);;
}
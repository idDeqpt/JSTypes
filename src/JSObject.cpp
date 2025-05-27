#include "JSTypes/JSObject.hpp"

#include <iostream>
#include <utility>
#include <string>


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

	fields.push_back(std::make_pair(key, new JSBaseType()));
	return true;
}

bool jst::JSObject::removeField(std::string key)
{
	for (unsigned int i = 0; i < fields.size(); i++)
		if (fields[i].first == key)
		{
			//if (fields[i].second != this)
			//{
				fields[i].second->destroy();
				delete fields[i].second;
			//}
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
		return "undefined";

	std::string result = "{";
	for (unsigned int i = 0; i < fields.size(); i++)
		result += fields[i].first + ":" + ((fields[i].second == this) ? "undefined" : fields[i].second->toString()) + ",";

	result.pop_back();
	result += "}";
	return result;
}

void jst::JSObject::destroy()
{
	for (unsigned int i = 0; i < fields.size(); i++)
	{
		//if (fields[i].second == this)
		//	continue;
		fields[i].second->destroy();
		delete fields[i].second;
	}	
}


jst::JSBaseType*& jst::JSObject::operator[](std::string key)
{
	for (unsigned int i = 0; i < fields.size(); i++)
		if (key == fields[i].first)
			return fields[i].second;
	return fields[0].second;
}
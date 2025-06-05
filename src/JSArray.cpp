#include "JSTypes/JSArray.hpp"

#include <vector>
#include <string>


jst::JSArray::JSArray()
{
	undefined = true;
	values.clear();
}

jst::JSArray::~JSArray()
{
	destroy();
}


void jst::JSArray::pushBack(std::shared_ptr<JSBaseType> new_value_ptr)
{
	values.push_back(new_value_ptr);
}

void jst::JSArray::popBack()
{
	values.pop_back();
}

std::shared_ptr<jst::JSBaseType>& jst::JSArray::back()
{
	return values.back();
}

unsigned int jst::JSArray::size()
{
	return values.size();
}


std::string jst::JSArray::toString()
{
	if (values.size() > 0)
		undefined = false;

	if (undefined)
		return "undefined";

	std::string result = "[";
	for (unsigned int i = 0; i < values.size(); i++)
		result += ((values[i].get() == this) ? "self" : values[i]->toString()) + ",";

	if (values.size() > 0)
		result.pop_back();
	result += "]";
	return result;
}

void jst::JSArray::destroy()
{
	values.clear();
	undefined = true;
}


std::shared_ptr<jst::JSBaseType>& jst::JSArray::operator[](unsigned int index)
{
	return values[index];
}
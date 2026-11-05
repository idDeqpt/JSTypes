#include <JSTypes/JSArray.hpp>

#include <vector>
#include <string>

namespace jst
{

JSArray::~JSArray()
{
	destroy();
}


void JSArray::pushBack(std::shared_ptr<JSBaseType> new_value_ptr)
{
	m_undefined = false;
	m_values.push_back(new_value_ptr);
}

void JSArray::popBack()
{
	m_values.pop_back();
}


std::shared_ptr<JSBaseType>& JSArray::back()
{
	return m_values.back();
}

unsigned int JSArray::size() const
{
	return m_values.size();
}


std::string JSArray::toString() const
{
	if (m_undefined)
		return "null";

	std::string result = "[";
	for (unsigned int i = 0; i < m_values.size(); i++)
		result += ((m_values[i].get() == this) ? "null" : m_values[i]->toString()) + ",";

	if (m_values.size() > 0)
		result.pop_back();
	result += "]";
	return result;
}

void JSArray::destroy()
{
	m_values.clear();
	m_undefined = true;
}


std::shared_ptr<JSBaseType>& JSArray::operator[](unsigned int index)
{
	return m_values[index];
}

} //namespace jst
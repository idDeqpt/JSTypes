#include <JSTypes/JSObject.hpp>

#include <JSTypes/JSUndefined.hpp>

#include <utility>
#include <string>
#include <memory>

namespace jst
{

std::shared_ptr<JSBaseType> JSObject::s_null_element = std::shared_ptr<JSBaseType>(nullptr);


JSObject::~JSObject()
{
	destroy();
}


bool JSObject::addField(std::string key)
{
	m_undefined = false;
	for (unsigned int i = 0; i < m_fields.size(); i++)
		if (m_fields[i].first == key)
			return false;

	m_fields.push_back(std::make_pair(key, std::make_shared<JSUndefined>()));
	return true;
}

bool JSObject::addField(std::string key, std::shared_ptr<JSBaseType> value_ptr)
{
	m_undefined = false;
	for (unsigned int i = 0; i < m_fields.size(); i++)
		if (m_fields[i].first == key) 
			return false;

	m_fields.push_back(std::make_pair(key, value_ptr));
	return true;
}

bool JSObject::removeField(std::string key)
{
	for (unsigned int i = 0; i < m_fields.size(); i++)
		if (m_fields[i].first == key)
		{
			if (m_fields[i].second.get() != this)
				m_fields[i].second->destroy();
			m_fields.erase(m_fields.begin() + i);
			return true;
		}
	return false;
}


std::string JSObject::toString() const
{
	if (m_undefined)
		return "null";

	std::string result = "{";
	for (unsigned int i = 0; i < m_fields.size(); i++)
		result += "\"" + m_fields[i].first + "\":" + ((m_fields[i].second.get() == this) ? "null" : m_fields[i].second->toString()) + ",";

	if (m_fields.size() > 0)
		result.pop_back();
	result += "}";
	return result;
}

void JSObject::destroy()
{
	m_fields.clear();
	m_undefined = true;
}


std::shared_ptr<JSBaseType>& JSObject::operator[](const std::string& key)
{
	for (unsigned int i = 0; i < m_fields.size(); i++)
		if (key == m_fields[i].first)
			return m_fields[i].second;
	return s_null_element;
}

} //namespace jst
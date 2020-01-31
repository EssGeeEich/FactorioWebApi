#include "QWebApi/metatypeimpl.h"

namespace WebApi {

MetaTypeImpl::MetaTypeImpl(QObject* parent)
	: QObject(parent), m_type(typeid(nullptr)), m_data(nullptr)
{}

void MetaTypeImpl::Set(std::type_index type, void* data)
{
	m_type = type;
	m_data = data;
}

void* MetaTypeImpl::Get(std::type_index type) const
{
	return (type == m_type) ? m_data : nullptr;
}

}

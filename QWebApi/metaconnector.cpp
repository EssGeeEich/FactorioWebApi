#include "QWebApi/metaconnector.h"

namespace WebApi {

MetaConnector::MetaConnector()
	: m_connector(std::make_shared<MetaConnectorImpl>()) {}

MetaConnectorImpl* MetaConnector::operator -> () const { return &(*(m_connector)); }
MetaConnectorImpl& MetaConnector::operator * () const { return *(m_connector); }
MetaConnectorImpl* MetaConnector::get() const { return m_connector.get(); }

}

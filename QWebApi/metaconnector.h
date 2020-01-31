#ifndef QWEBAPI_METACONNECTOR_H
#define QWEBAPI_METACONNECTOR_H
#include "QWebApi/WebApi_global.h"
#include "QWebApi/metaconnectorimpl.h"
#include <memory>

namespace WebApi {

class MetaConnector {
	std::shared_ptr<MetaConnectorImpl> m_connector;
public:
	MetaConnector();
	MetaConnectorImpl* operator -> () const;
	MetaConnectorImpl& operator * () const;
	MetaConnectorImpl* get() const;
};

}

#endif // QWEBAPI_METACONNECTOR_H

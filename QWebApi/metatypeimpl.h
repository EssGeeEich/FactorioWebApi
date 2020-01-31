#ifndef QWEBAPI_METATYPEIMPL_H
#define QWEBAPI_METATYPEIMPL_H
#include "QWebApi/WebApi_global.h"
#include <QObject>
#include <typeindex>

namespace WebApi {

class MetaTypeImpl : public QObject {
	Q_OBJECT;
	std::type_index m_type;
	void* m_data;
protected:
	explicit MetaTypeImpl(QObject* parent);
	void Set(std::type_index, void*);
	void* Get(std::type_index) const;
};

}
#endif // QWEBAPI_METATYPEIMPL_H

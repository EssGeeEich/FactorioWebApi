#ifndef QWEBAPI_METATYPE_H
#define QWEBAPI_METATYPE_H
#include "QWebApi/WebApi_global.h"
#include "QWebApi/metatypeimpl.h"

namespace WebApi {

class MetaType : public MetaTypeImpl {
	Q_OBJECT;
public:
	explicit MetaType(QObject*);

	template <typename T>
	MetaType(QObject* p, T* d)
		: MetaType(p)
	{
		Set(d);
	}

	template <typename T>
	T* Get() {
		return static_cast<T*>(MetaTypeImpl::Get(typeid(T)));
	}
	template <typename T>
	MetaType& Set(T* ptr) {
		MetaTypeImpl::Set(typeid(T), static_cast<void*>(ptr));
		return *this;
	}
};

}

#endif // QWEBAPI_METATYPE_H

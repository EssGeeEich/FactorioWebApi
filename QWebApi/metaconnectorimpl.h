#ifndef QWEBAPI_METACONNECTORIMPL_H
#define QWEBAPI_METACONNECTORIMPL_H
#include "QWebApi/WebApi_global.h"
#include "QWebApi/metatype.h"

namespace WebApi {

class MetaConnectorImpl : public QObject {
	Q_OBJECT;

	template <typename> friend class ConnectorSetter;
protected:
	void emitFinished(MetaType* payload);
	void emitProgress(MetaType* payload);
signals:
	void onProgress(MetaType*);
	void onFinished(MetaType*);
};

}

#endif // QWEBAPI_METACONNECTORIMPL_H

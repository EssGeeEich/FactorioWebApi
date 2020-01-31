#include "QWebApi/metaconnectorimpl.h"

namespace WebApi {

void MetaConnectorImpl::emitFinished(MetaType *payload)
{
	emit onFinished(payload);
}

void MetaConnectorImpl::emitProgress(MetaType *payload)
{
	emit onProgress(payload);
}

}

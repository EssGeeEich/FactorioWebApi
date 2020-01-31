#ifndef QWEBAPI_CONNECTORSETTER_H
#define QWEBAPI_CONNECTORSETTER_H
#include "QWebApi/WebApi_global.h"
#include "QWebApi/metaconnector.h"
#include "QWebApi/result.h"
#include <QObject>
#include <typeindex>
#include <memory>

namespace WebApi {

template <typename T>
class ConnectorSetter {
	ResponseCode m_failureResult;
	MetaConnector m_connector;
	bool m_finished;
public:
	ConnectorSetter(MetaConnector connector)
		: m_failureResult(RC_FAILED_GENERIC),
		  m_connector(std::move(connector)),
		  m_finished(false)
	{}
	~ConnectorSetter()
	{
		Finish(m_failureResult);
	}
	void SetFailureError(ResponseCode failureResult)
	{
		m_failureResult = failureResult;
	}

	template <typename ... Args>
	void Finish(ResponseCode result, Args&& ... args)
	{
		if(m_finished)
			return;

		Result<T> r(result, std::forward<Args>(args)...);
		MetaType mt(m_connector.get(), &r);
		m_connector->emitFinished(&mt);
		m_finished = true;
	}
	template <typename ... Args>
	void Progress(ResponseCode result, Args&& ... args)
	{
		Result<T> r(result, std::forward<Args>(args)...);
		MetaType mt(m_connector.get(), &r);
		m_connector->emitProgress(&mt);
	}
};

}

#endif // QWEBAPI_CONNECTORSETTER_H

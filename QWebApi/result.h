#ifndef QWEBAPI_RESULT_H
#define QWEBAPI_RESULT_H
#include "QWebApi/WebApi_global.h"
#include <memory>

namespace WebApi {

enum ResponseCode {
	RC_OK = 0,
	RC_FAILED_GENERIC,
	RC_LOGIN_FAILED,
	RC_REQUEST_FAILED
};

template <typename T>
class Result
{
	ResponseCode m_response;
	std::shared_ptr<T> m_data;
public:
	template <typename T1, typename ... Args>
	Result(ResponseCode apiResponse, T1&& arg1, Args&& ... args)
		: m_response(apiResponse),
		  m_data(std::make_shared<T>(std::forward<T1>(arg1), std::forward<Args>(args)...))
	{}

	Result(ResponseCode apiResponse)
		: m_response(apiResponse) {}

	T* Get() { return m_data.get(); }
	T const* Get() const { return m_data.get(); }

	ResponseCode Response() const { return m_response; }
};

}

#endif // QWEBAPI_RESULT_H

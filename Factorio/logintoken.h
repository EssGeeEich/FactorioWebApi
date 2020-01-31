#ifndef QWEBAPI_FACTORIO_LOGINTOKEN_H
#define QWEBAPI_FACTORIO_LOGINTOKEN_H
#include "Factorio/core.h"
#include <QString>

namespace Factorio {
	struct CLIWEBAPI_EXPORT LoginToken {
		QString m_username;
		QString m_token;
	};
}

#endif // QWEBAPI_FACTORIO_LOGINTOKEN_H

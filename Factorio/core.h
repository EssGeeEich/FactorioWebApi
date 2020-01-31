#ifndef QWEBAPI_FACTORIO_CORE_H
#define QWEBAPI_FACTORIO_CORE_H

#include "QWebApi/core.h"
#include "QWebApi/manager.h"

namespace Factorio {

struct LoginToken;

class CLIWEBAPI_EXPORT Api : public QObject
{
	Q_OBJECT;
	WebApi::Manager m_mgr;
public:
	explicit Api(QObject* parent);

	// WebApi::Result<Factorio::LoginToken>
	WebApi::MetaConnector
		TryLogin(std::string const& username,
		  std::string const& password,
		  bool require_game_ownership =true);

	// WebApi::Result<bool>
	WebApi::MetaConnector
		ValidateLogin(Factorio::LoginToken const&);

	// WebApi::Result<Factorio::ModList>
	WebApi::MetaConnector
		GetMods(LoginToken const&, int PageSize, int PageNumber);

	// WebApi::Result<Factorio::FullModInfo>
	WebApi::MetaConnector
		GetFullModInfo(LoginToken const&, QString modName);
};

}

#endif // QWEBAPI_FACTORIO_CORE_H

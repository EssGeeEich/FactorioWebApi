#ifndef QWEBAPI_MANAGER_H
#define QWEBAPI_MANAGER_H

#include "QWebApi/WebApi_global.h"
#include "QWebApi/core.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QUrlQuery>
#include <queue>
#include <functional>
#include <mutex>

namespace WebApi {

class WEBAPI_EXPORT Manager : public QObject {
	Q_OBJECT;
	QNetworkAccessManager* m_networkAccessManager;
	QSslConfiguration m_sslConfiguration;
public:
	Manager(QObject* parent);

	QNetworkRequest newNetworkRequest();

	void Post(MetaConnector, QNetworkRequest const&, QByteArray const&, std::function<void(QNetworkReply*, MetaConnector)>);
	void Get(MetaConnector, QNetworkRequest const&, std::function<void(QNetworkReply*, MetaConnector)>);
};

}

#endif // QWEBAPI_MANAGER_H

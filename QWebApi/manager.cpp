#include "QWebApi/manager.h"
#include <QCoreApplication>
#include <thread>
#include <iostream>

namespace WebApi {

static QString const UserAgent = QString()
	+ "QT/"
	+ QT_VERSION_STR
	+ " (FactorioWebApi)"
;

Manager::Manager(QObject* parent)
	: QObject(parent),
	  m_networkAccessManager(new QNetworkAccessManager(this)),
	  m_sslConfiguration(QSslConfiguration::defaultConfiguration())
{}

QNetworkRequest Manager::newNetworkRequest()
{
	QNetworkRequest request;
	request.setSslConfiguration(m_sslConfiguration);
	request.setHeader(QNetworkRequest::UserAgentHeader, UserAgent);
	return request;
}

void Manager::Post(MetaConnector connector, QNetworkRequest const& request, QByteArray const& postData,
	std::function<void (QNetworkReply *, MetaConnector)> callback)
{
	QNetworkReply* reply = m_networkAccessManager->post(request, postData);
	if(!reply)
	{
		callback(nullptr, connector);
		return;
	}

	QObject::connect(reply, &QNetworkReply::finished, [=](){
		callback(reply, connector);
	});
}

void Manager::Get(MetaConnector connector, QNetworkRequest const& request,
	std::function<void (QNetworkReply *, MetaConnector)> callback)
{
	QNetworkReply* reply = m_networkAccessManager->get(request);
	if(!reply)
	{
		callback(nullptr, connector);
		return;
	}

	QObject::connect(reply, &QNetworkReply::finished, [=](){
		callback(reply, connector);
	});
}


}

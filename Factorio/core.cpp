#include "Factorio/core.h"
#include "Factorio/logintoken.h"
#include "Factorio/mods.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

namespace Factorio {
	Api::Api(QObject *parent)
		: QObject(parent),
		  m_mgr(this)
	{}

	WebApi::MetaConnector
		Api::ValidateLogin(LoginToken const& token)
	{
		WebApi::MetaConnector connector;

		QUrl url("https://updater.factorio.com/get-available-versions");
		QUrlQuery getData;
		getData.addQueryItem("username", token.m_username);
		getData.addQueryItem("token", token.m_token);
		url.setQuery(getData);

		QNetworkRequest request = m_mgr.newNetworkRequest();
		request.setUrl(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/x-www-form-urlencoded"));

		m_mgr.Get(connector, request, [](QNetworkReply* reply, WebApi::MetaConnector connector){
		// GET RESULT RECEIVED
			WebApi::ConnectorSetter<bool> wfs(connector);
			if(!reply || reply->error() != QNetworkReply::NoError)
				return;

			QByteArray qba = reply->readAll();
			QJsonDocument qjd = QJsonDocument::fromJson(qba);
			QJsonObject json = qjd.object();

			if(json.contains("status"))
				return;

			wfs.Finish(WebApi::RC_OK, true);
		// END
		});

		return connector;
	}

	WebApi::MetaConnector
		Api::TryLogin(std::string const& username,
			std::string const& password,
			bool require_game_ownership)
	{
		WebApi::MetaConnector connector;

		QNetworkRequest request = m_mgr.newNetworkRequest();
		request.setUrl(QUrl("https://auth.factorio.com/api-login"));
		request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/x-www-form-urlencoded"));

		QUrlQuery postData;
		postData.addQueryItem("username", QString::fromStdString(username));
		postData.addQueryItem("password", QString::fromStdString(password));
		postData.addQueryItem("api_version", "2");
		postData.addQueryItem("require_game_ownership", require_game_ownership ? QString("true") : QString("false"));

		m_mgr.Post(connector, request, postData.toString(QUrl::FullyEncoded).toUtf8(),
			[](QNetworkReply* reply, WebApi::MetaConnector connector){
			// POST RESULT RECEIVED
				WebApi::ConnectorSetter<LoginToken> wfs(connector);
				if(!reply || reply->error() != QNetworkReply::NoError)
					return;

				wfs.SetFailureError(WebApi::RC_LOGIN_FAILED);

				QByteArray qba = reply->readAll();
				QJsonDocument qjd = QJsonDocument::fromJson(qba);
				QJsonObject json = qjd.object();

				if(json.contains("token"))
				{
					wfs.Finish(WebApi::RC_OK,
						LoginToken{
							json["username"].toString(),
							json["token"].toString()
						}
					);
				}
			// END
			}
		);
		return connector;
	}

	WebApi::MetaConnector
		Api::GetMods(LoginToken const&, int PageSize, int PageNumber)
	{
		// token is currently optional
		WebApi::MetaConnector connector;

		QUrl url("https://mods.factorio.com/api/mods");
		QUrlQuery getData;
		getData.addQueryItem("page_size", QString::number(PageSize));
		getData.addQueryItem("page", QString::number(PageNumber));
		url.setQuery(getData);

		QNetworkRequest request = m_mgr.newNetworkRequest();
		request.setUrl(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/x-www-form-urlencoded"));

		m_mgr.Get(connector, request, [](QNetworkReply* reply, WebApi::MetaConnector connector){
		// GET RESULT RECEIVED
			WebApi::ConnectorSetter<ModList> wfs(connector);
			if(!reply || reply->error() != QNetworkReply::NoError)
				return;
			wfs.SetFailureError(WebApi::RC_REQUEST_FAILED);

			QByteArray qba = reply->readAll();
			QJsonDocument qjd = QJsonDocument::fromJson(qba);
			QJsonObject json = qjd.object();

			if(json.contains("results"))
			{
				QJsonArray results = json["results"].toArray();
				QVector<ModInfo> mods;
				mods.reserve(results.count());
				for(auto result : results)
				{
					QJsonObject modObj = result.toObject();

					QVector<ModReleaseInfo> releases;

					if(modObj.contains("latest_release"))
					{
						QJsonObject rel = modObj["latest_release"].toObject();
						QJsonObject info = rel["info_json"].toObject();

						releases.push_back(
							ModReleaseInfo{
								QUrl(rel["download_url"].toString()),
								rel["file_name"].toString(),
								info["factorio_version"].toString(),
								QDateTime::fromString(
									rel["released_at"].toString(),
									"yyyy-MM-ddTHH:mm:ss.zzz000Z"
								),
								rel["version"].toString(),
								rel["sha1"].toString()
							}
						);
					}

					mods.push_back(
						ModInfo{
							modObj["name"].toString(),
							modObj["title"].toString(),
							modObj["owner"].toString(),
							modObj["summary"].toString(),
							modObj["downloads"].toInt(),
							modObj["score"].toDouble(),
							QUrl(QString("https://mods.factorio.com/" + modObj["thumbnail"].toString())),
							std::move(releases)
						}
					);
				}

				QJsonObject pagination = json["pagination"].toObject();
				wfs.Finish(WebApi::RC_OK,
					ModList {
						std::move(mods),
						pagination["page"].toInt(),
						pagination["page_count"].toInt(),
						pagination["page_size"].toInt(),
						pagination["count"].toInt()
					}
				);
			}
		// END
		});

		return connector;
	}

	WebApi::MetaConnector
		Api::GetFullModInfo(LoginToken const&, QString modName)
	{
		// token is currently optional
		WebApi::MetaConnector connector;

		QUrl url("https://mods.factorio.com/api/mods/" + modName.replace('/','_').replace('\\','_') + "/full");

		QNetworkRequest request = m_mgr.newNetworkRequest();
		request.setUrl(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/x-www-form-urlencoded"));

		m_mgr.Get(connector, request, [](QNetworkReply* reply, WebApi::MetaConnector connector){
		// GET RESULT RECEIVED
			WebApi::ConnectorSetter<FullModInfo> wfs(connector);
			if(!reply || reply->error() != QNetworkReply::NoError)
				return;
			wfs.SetFailureError(WebApi::RC_REQUEST_FAILED);

			QByteArray qba = reply->readAll();
			QJsonDocument qjd = QJsonDocument::fromJson(qba);
			QJsonObject json = qjd.object();

			if(json.contains("name"))
			{
				QJsonObject license = json["license"].toObject();
				QJsonObject tag = json["tag"].toObject();

				QVector<ModReleaseInfo> modReleases;
				QJsonArray releases = json["releases"].toArray();
				for(auto it = releases.begin(); it != releases.end(); ++it)
				{
					QJsonObject rel = it->toObject();
					QJsonObject info = rel["info_json"].toObject();
					modReleases.push_back(ModReleaseInfo{
						QUrl(rel["download_url"].toString()),
						rel["file_name"].toString(),
						info["factorio_version"].toString(),
						QDateTime::fromString(
							rel["released_at"].toString(),
							"yyyy-MM-ddTHH:mm:ss.zzz000Z"
						),
						rel["version"].toString(),
						rel["sha1"].toString()
					});
				}

				wfs.Finish(WebApi::RC_OK,
					FullModInfo {
						ModInfo {
							json["name"].toString(),
							json["title"].toString(),
							json["owner"].toString(),
							json["summary"].toString(),
							json["downloads"].toInt(),
							json["score"].toDouble(),
							QUrl(QString("https://mods.factorio.com/" + json["thumbnail"].toString())),
							std::move(modReleases)
						},
						json["category"].toString(),
						json["changelog"].toString(),
						QDateTime::fromString(
							json["created_at"].toString(),
							"yyyy-MM-ddTHH:mm:ss.zzz000Z"
						),
						json["description"].toString(),
						QUrl(json["github_path"].toString()),
						QUrl(json["homepage"].toString()),
						license["name"].toString(),
						QUrl(license["url"].toString()),
						tag["name"].toString()
					}
				);
			}
		// END
		});

		return connector;
	}
}

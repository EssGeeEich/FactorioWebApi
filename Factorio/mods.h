#ifndef QWEBAPI_FACTORIO_MODS_H
#define QWEBAPI_FACTORIO_MODS_H
#include "Factorio/core.h"
#include <QString>
#include <QVector>
#include <QUrl>

namespace Factorio {
	struct CLIWEBAPI_EXPORT ModReleaseInfo {
		QUrl m_downloadUrl;
		QString m_filename;
		QString m_factorioVersion;
		QDateTime m_releaseTime;
		QString m_modVersion;
		QString m_sha1;
	};
	struct CLIWEBAPI_EXPORT ModInfo {
		QString m_name;
		QString m_title;
		QString m_owner;
		QString m_summary;
		int m_downloads;
		double m_score;
		QUrl m_thumbnail;
		QVector<ModReleaseInfo> m_releases;
	};
	struct CLIWEBAPI_EXPORT FullModInfo {
		ModInfo m_basicInfo;
		QString m_category;
		QString m_changelog;
		QDateTime m_creationTime;
		QString m_description;
		QUrl m_github;
		QUrl m_homepage;
		QString m_licenseName;
		QUrl m_licenseUrl;
		QString m_tag;
	};
	struct CLIWEBAPI_EXPORT ModList {
		QVector<ModInfo> m_mods;
		int m_page;
		int m_pagecount;
		int m_pagesize;
		int m_results;
	};
}

#endif // QWEBAPI_FACTORIO_MODS_H

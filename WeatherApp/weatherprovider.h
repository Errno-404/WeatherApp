#ifndef WEATHERPROVIDER_H
#define WEATHERPROVIDER_H

#include <QObject>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QPixmap>
#include "weatherdata.h"

class weatherProvider : public QObject
{
    Q_OBJECT



public:
    weatherProvider(QString apiKey);

    ~weatherProvider();

    QJsonObject getCurrentWeatherData(QString);
    WeatherData* getWeatherDataForecast(QString);
    int getRequestStatus() const{
        return requestStatus;
    }

    QList<QPixmap>* downloadWeatherIcons(QList<QUrl> iconUrls);






private:
    // manager as a service
    QNetworkAccessManager* manager;
    QString apiKey;
    QList<QPixmap> weatherIcons;
    int requestStatus;

    QJsonObject getWeatherDataJSON(QList<std::tuple<QString, QString>>);

};

#endif // WEATHERPROVIDER_H

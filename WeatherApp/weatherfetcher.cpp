#include "weatherfetcher.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

WeatherFetcher::WeatherFetcher(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &WeatherFetcher::handleNetworkResponse);
}

void WeatherFetcher::fetchWeatherData(const QString &apiKey, const QString &location)
{
    QString url = "http://api.weatherapi.com/v1/current.json?key=" + apiKey + "&q=" + location;
    QNetworkReply *reply = m_networkManager.get(QNetworkRequest(QUrl(url)));
    // ... handling errors and cleanup omitted for brevity ...
}

void WeatherFetcher::handleNetworkResponse()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();

        QString temperature = jsonObject["current"].toObject()["temp_c"].toString();
        QString condition = jsonObject["current"].toObject()["condition"].toObject()["text"].toString();

        emit weatherDataFetched(temperature, condition);
    }

    reply->deleteLater();
}

#ifndef WEATHERFETCHER_H
#define WEATHERFETCHER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


class WeatherFetcher: public QObject
{    
    Q_OBJECT

public:
    explicit WeatherFetcher(QObject *parent = nullptr);

    void fetchWeatherData(const QString &apiKey, const QString &location);

signals:
    void weatherDataFetched(const QString &temperature, const QString &condition);

private slots:
    void handleNetworkResponse();

private:
    QNetworkAccessManager m_networkManager;


};

#endif // WEATHERFETCHER_H

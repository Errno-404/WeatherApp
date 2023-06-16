#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include<QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


class WeatherData
{
public:
    WeatherData();
    QList<QDate> getDates() const;
    QList<double> getMaxTemperatures() const;
    QList<double> getMinTemperatures() const;
    QList<QUrl> getIconsUrls() const;
    QList<int> getRains() const;

    double getCurrentTemperature() const;
    double getCurrentWindKph() const;
    QString getCurrentWindDirection() const;
    int getCurrentHumidity() const;

    void parseJSONToWeatherData(const QJsonObject& data);


private:

    QList<QDate> dates;
    QList<double> max_temperatures;
    QList<double> min_temperatures;
    QList<QUrl> icons;
    QList<int> rains;


    double currentTemp;
    double currentWindKph;
    QString currentWindDir;
    int currentHumidity;
    QUrl currentIconUrl;
    QPixmap currentIcon;
    QList<QPixmap> weatherIcons;







};

#endif // WEATHERDATA_H

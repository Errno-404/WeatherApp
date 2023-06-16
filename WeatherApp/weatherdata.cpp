#include "weatherdata.h"

WeatherData::WeatherData()
{

}

// json structure:
/*
 *
 *  doc:
 *      location:
 *          name
 *          country
 *          localtime
 *      current:
 *          temp_c
 *          condition:
 *              icon
 *          wind_kph
 *          wind_dir
 *          humidity
 *      forecast:
 *          forecastday:
 *              [
 *                  date
 *                  day:
 *                      maxtemp_c
 *                      mintemp_c
 *                      condition:
 *                          icon
 *                  astro:
 *                      //todo
 *                  hour:
 *                      [
 *                          chance_of_rain
 *
 */

void WeatherData::parseJSONToWeatherData(const QJsonObject& data)
{
    QDateTime sysTime = QDateTime::currentDateTime();

    // weather forecast for current day
    QJsonObject current = data["current"].toObject();


    currentTemp = current["temp_c"].toDouble();
    currentWindKph = current["wind_kph"].toDouble();
    currentWindDir = current["wind_dir"].toString();
    currentHumidity = current["humidity"].toInt();
    QJsonObject condition = current["condition"].toObject();
    QString strIcon = condition["icon"].toString();
    strIcon = "https:" + strIcon;
    QUrl icon = QUrl(strIcon);
    icons.append(icon);


    // weather forecast for each day
    QJsonObject forecast = data["forecast"].toObject();
    QJsonArray forecastDays = forecast["forecastday"].toArray();


    for(const QJsonValue& forecastDayValue: forecastDays){
        QJsonObject forecastDayObject = forecastDayValue.toObject();

        //data
        QString strDate = forecastDayObject["date"].toString();
        QDate date = QDate::fromString(strDate, Qt::ISODateWithMs);
        dates.append(date);


        QJsonObject day = forecastDayObject["day"].toObject();


        double max_temp_c = day["maxtemp_c"].toDouble();
        max_temperatures.append(max_temp_c);


        double min_temp_c = day["mintemp_c"].toDouble();
        min_temperatures.append(min_temp_c);

        QJsonObject condition = day["condition"].toObject();

        QString strIcon = condition["icon"].toString();
        strIcon = "https:" + strIcon;
        QUrl icon = QUrl(strIcon);
        icons.append(icon);

        QJsonArray hours = forecastDayObject["hour"].toArray();


        // weather forecast for each hour
        for(const QJsonValue& hourValue: hours){


            QJsonObject hourObject = hourValue.toObject();
            //data
            QDateTime time = QDateTime::fromString(hourObject["time"].toString(),"yyyy-MM-dd hh:mm");

            if((time.time().hour() == sysTime.time().hour()) && (time.date() == sysTime.date())){
                int chance_of_rain = hourObject["chance_of_rain"].toInt();
                rains.append(chance_of_rain);
            }


        }
    }

}


QList<QDate> WeatherData::getDates() const
{
    return dates;
}

QList<double> WeatherData::getMaxTemperatures() const
{
    return max_temperatures;
}

QList<double> WeatherData::getMinTemperatures() const
{
    return min_temperatures;
}

QList<QUrl> WeatherData::getIconsUrls() const
{
    return icons;
}

QList<int> WeatherData::getRains() const
{
    return rains;
}

double WeatherData::getCurrentTemperature() const
{
    return currentTemp;
}

double WeatherData::getCurrentWindKph() const
{
    return currentWindKph;
}

QString WeatherData::getCurrentWindDirection() const
{
    return currentWindDir;
}

int WeatherData::getCurrentHumidity() const
{
    return currentHumidity;
}




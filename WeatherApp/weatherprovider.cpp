#include "weatherprovider.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <weatherdata.h>

weatherProvider::weatherProvider(QString apiKey)
{
    manager = new QNetworkAccessManager(this);
    this->apiKey = apiKey;
}

WeatherData* weatherProvider::getWeatherDataForecast(QString location){
    QString param_endpoint = "forecast.json";
    QString param_q = location;
    QString param_days = "7";
    QString param_aqi = "no";
    QString param_alerts = "no";

    QList<std::tuple<QString, QString>> parameters_map;
    parameters_map.append(std::make_tuple("endpoint", param_endpoint));
    parameters_map.append(std::make_tuple("q", param_q));
    parameters_map.append(std::make_tuple("days", param_days));
    parameters_map.append(std::make_tuple("aqi", param_aqi));
    parameters_map.append(std::make_tuple("alerts", param_alerts));

    QJsonObject weatherForecactJson = getWeatherDataJSON(parameters_map);
    if(weatherForecactJson.isEmpty()){
        WeatherData* wd = new WeatherData();
        return wd;
    }
    WeatherData* wd = new WeatherData();
    wd->parseJSONToWeatherData(weatherForecactJson);


    return wd;
}

QJsonObject weatherProvider::getWeatherDataJSON(QList<std::tuple<QString, QString>> parameters){

    QString strUrl = "http://api.weatherapi.com/v1/" + std::get<1>(parameters.at(0)) + "?key=" + apiKey;
    auto iter = parameters.begin();
    std::advance(iter, 1); //shift iterator to [1]

    for(; iter!= parameters.end(); ++iter){

        std::tuple<QString, QString>& tuple = *iter;
        QString param = std::get<0>(tuple);
        QString value = std::get<1>(tuple);


        strUrl += "&" + param + "=" + value;
    }

    QNetworkRequest request;
    request.setUrl(QUrl(strUrl));
    QNetworkReply * reply = manager->get(request);


    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonObject jsonReply;
    if (reply->error() == QNetworkReply::NoError) {

        requestStatus = 1;
        QByteArray response = reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);

        jsonReply = jsonResponse.object();



    } else {
        qDebug() << "Error: " << reply->errorString();
        requestStatus = 0;
    }


    reply->deleteLater();
    return jsonReply;
}

QList<QPixmap>* weatherProvider::downloadWeatherIcons(QList<QUrl> urls){
    QList<QPixmap>* icons = new QList<QPixmap>();

    for (int i = 0; i < urls.size(); ++i)
    {
        QEventLoop eventLoop;
        QNetworkReply* reply = manager->get(QNetworkRequest(urls[i]));

        QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();

        if (reply->error() == QNetworkReply::NoError)
        {
            requestStatus = 1;
            QByteArray data = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(data);
            (*icons).append(pixmap);
        }
        else{
            qDebug() << "Cannot fetch data";
            requestStatus = 0;
        }

        reply->deleteLater();
    }

    return icons;
}



weatherProvider::~weatherProvider(){
    delete manager;
}



#include "mainwindow.h"
#include "weatherprovider.h"
#include <QApplication>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


void handleWeatherData(const QString &temperature, const QString &condition)
{
    // Obsługa danych pogodowych
    qDebug() << "Temperature: " << temperature;
    qDebug() << "Condition: " << condition;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Pogoda :)");
    w.setFixedSize(614, 340);
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    w.show();
    return a.exec();


}

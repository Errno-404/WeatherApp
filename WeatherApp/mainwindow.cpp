#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>
#include <weatherprovider.h>
#include "weatherdata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wp = new weatherProvider("10697164b6214d06b62130425231506");
    QString location = "Cracow";
//    data = wp->getWeatherDataForecast(location);
    updateGui(location);
}

MainWindow::~MainWindow()
{
    delete wp;
    delete data;
    delete ui;
}


void MainWindow::updateGui(QString city){
    data = wp->getWeatherDataForecast(city);
    if(data->getDates().isEmpty()){

        ui->txtError->setText("Nie znaleziono miasta");
        ui->txtError->setStyleSheet("QLabel {color: red}");
        ui->txtError->adjustSize();
        ui->txtError->setVisible(true);
        return;
    }
    ui->txtError->setVisible(false);

    icons = wp->downloadWeatherIcons(data->getIconsUrls());


    ui->txtError->setVisible(false);
    ui->cityLine->setText(city);
    ui->txtCurrentHumidity->setText(QString::number(data->getCurrentHumidity()) + " %");
    ui->txtCurrTemp->setText(QString::number(data->getCurrentTemperature()));

    ui->txtCurrentRain->setText(QString::number(data->getRains().at(0)) + " %");
    ui->txtCurrentWind->setText(QString::number(data->getCurrentWindKph()) + "km/h " + data->getCurrentWindDirection());

    ui->img0->setPixmap(icons->at(0));
    ui->img1->setPixmap(icons->at(1));
    ui->img2->setPixmap(icons->at(2));
    ui->img3->setPixmap(icons->at(3));
    ui->img4->setPixmap(icons->at(4));
    ui->img5->setPixmap(icons->at(5));
    ui->img6->setPixmap(icons->at(6));
    ui->img7->setPixmap(icons->at(7));


    // days
    QDate currentDate = QDate::currentDate();
    int today = currentDate.dayOfWeek();
    today --; // indexing from 0

    QString strDays[] = {"pn.", "wt.", "śr.", "czw.", "pt.", "sob.", "nd."};
    QString daysShifted[7];


    for(int i=0; i<7; ++i){
        daysShifted[i] = strDays[(today + i) % 7];
    }


    ui->day1->setText(daysShifted[0]);
    ui->day2->setText(daysShifted[1]);
    ui->day3->setText(daysShifted[2]);
    ui->day4->setText(daysShifted[3]);
    ui->day5->setText(daysShifted[4]);
    ui->day6->setText(daysShifted[5]);
    ui->day7->setText(daysShifted[6]);



    // min_max_temps:

    QList<double> maxTemps = data->getMaxTemperatures();
    QList<double> minTemps = data->getMinTemperatures();

    ui->maxDay1->setText(QString::number(qRound(maxTemps.at(0))) + " °");
    ui->minDay1->setText(QString::number(qRound(minTemps.at(0))) + " °");


    ui->maxDay2->setText(QString::number(qRound(maxTemps.at(1))) + " °");
    ui->minDay2->setText(QString::number(qRound(minTemps.at(1))) + " °");

    ui->maxDay3->setText(QString::number(qRound(maxTemps.at(2))) + " °");
    ui->minDay3->setText(QString::number(qRound(minTemps.at(2))) + " °");


    ui->maxDay4->setText(QString::number(qRound(maxTemps.at(3))) + " °");
    ui->minDay4->setText(QString::number(qRound(minTemps.at(3))) + " °");


    ui->maxDay5->setText(QString::number(qRound(maxTemps.at(4))) + " °");
    ui->minDay5->setText(QString::number(qRound(minTemps.at(4))) + " °");

    ui->maxDay6->setText(QString::number(qRound(maxTemps.at(5))) + " °");
    ui->minDay6->setText(QString::number(qRound(minTemps.at(5))) + " °");

    ui->maxDay7->setText(QString::number(qRound(maxTemps.at(6))) + " °");
    ui->minDay7->setText(QString::number(qRound(minTemps.at(6))) + " °");




    delete icons;
}



void MainWindow::on_btnCity_clicked()
{
    QString city = ui->cityLine->text();
    updateGui(city);
}


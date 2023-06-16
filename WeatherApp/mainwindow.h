#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weatherprovider.h"
#include "weatherdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void updateGui(QString);
    ~MainWindow();

private slots:



    void on_btnCity_clicked();

private:
    Ui::MainWindow *ui;
    weatherProvider* wp;
    WeatherData* data;
    QList<QPixmap>* icons;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"

#include <QMainWindow>
#include "networker.h"
#include <QMap>
#include <QEventLoop>
#include <QNetworkReply>

enum RemoteRequest {
    FetchWeatherInfo,
    FetchWeatherIcon
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    class Private;
    friend class Private;
    Private *d;
};

class MainWindow::Private
{
public:
    Private(MainWindow *q) : mainWindow(q)
    {
        netWorker = NetWorker::instance();
    }

    void fetchWeather(const QString &cityName)
    {
        //netWorker->get(QString("http://api.openweathermap.org/data/2.5/weather?q=%1&lang=zh_cn&mode=json&APPID=1734ef2554f306a3a0d4cd8f94752db2").arg(cityName));
        //netWorker->get(QString("http://apistore.baidu.com/microservice/weather?cityid=成都"));
        /*QNetworkReply *reply = netWorker->get(QString("http://api.openweathermap.org/data/2.5/weather?q=%1&lang=zh_cn&mode=json&APPID=1734ef2554f306a3a0d4cd8f94752db2").arg(cityName));
        replyMap.insert(reply, FetchWeatherInfo);*/
        QEventLoop eventLoop;
        connect(netWorker, &NetWorker::finished,
                &eventLoop, &QEventLoop::quit);
        QNetworkReply *reply = netWorker->get(QString("http://api.openweathermap.org/data/2.5/weather?q=%1&mode=json&units=metric&lang=zh_cn&APPID=1734ef2554f306a3a0d4cd8f94752db2").arg(cityName));
        replyMap.insert(reply, FetchWeatherInfo);
        eventLoop.exec();
    }

    void fetchIcon(const QString &iconName)
    {
        QNetworkReply *reply = netWorker->get(QString("http://api.openweathermap.org/img/w/%1.png").arg(iconName));
        replyMap.insert(reply, FetchWeatherIcon);
    }

    NetWorker *netWorker;
    MainWindow *mainWindow;
    QMap<QNetworkReply *, RemoteRequest> replyMap;
};

#endif // MAINWINDOW_H

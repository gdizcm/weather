#include "global.h"

#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QObject>
#include <QTranslator>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTranslator t;
    t.load("E:/programs/Qt65Network/trans.qm");
    a.installTranslator(&t);


    MainWindow w;
    w.show();

    return a.exec();
}

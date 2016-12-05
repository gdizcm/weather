#include "global.h"

#include "networker.h"
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include <QNetworkProxy>

NetWorker *NetWorker::instance()
{
    static NetWorker netWorker;
    return &netWorker;
}

NetWorker::NetWorker(QObject *parent) :
    QObject(parent),
    d(new NetWorker::Private(this))
{
    connect(d->manager, &QNetworkAccessManager::finished,
            this, &NetWorker::finished);
    //connect(d->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(showGet(QNetworkReply*)));

}
//http://api.openweathermap.org/data/2.5/weather?q=Dalian,cn&lang=zh_cn&mode=xml&APPID=1734ef2554f306a3a0d4cd8f94752db2
NetWorker::~NetWorker()
{
    delete d;
    d = 0;
}

QNetworkReply * NetWorker::get(const QString &url)
{
    return d->manager->get(QNetworkRequest(QUrl(url)));
}

void NetWorker::showGet(QNetworkReply *reply)
{
    qDebug()<<"-------------------------------"<<reply->readAll();
}

NetWorker::Private::Private(NetWorker *q): manager(new QNetworkAccessManager(q))
{
    QNetworkProxy proxy(QNetworkProxy::HttpProxy, QStringLiteral("dl-proxy.neusoft.com"), 8080, "zhao-chm", "5tgb^YHN");
    manager->setProxy(proxy);
}

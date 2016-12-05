#ifndef NETWORKER_H
#define NETWORKER_H

#include "global.h"

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class NetWorker : public QObject
{
    Q_OBJECT
public:
    static NetWorker * instance();
    ~NetWorker();

    QNetworkReply * get(const QString &url);

private:
    class Private;
    friend class Private;
    Private *d;

    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
    NetWorker& operator=(NetWorker rhs) Q_DECL_EQ_DELETE;

signals:
    void finished(QNetworkReply *reply);

public slots:
    void showGet(QNetworkReply *reply);
};

class NetWorker::Private
{
public:
    Private(NetWorker *q);

    QNetworkAccessManager *manager;
};

#endif // NETWORKER_H

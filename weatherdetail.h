#ifndef WEATHERDETAIL_H
#define WEATHERDETAIL_H

#include "global.h"

#include <QString>
#include <QDateTime>
#include <QList>
#include <QDebug>

class WeatherDetail
{
public:
    WeatherDetail();
    ~WeatherDetail();

    QString desc() const;
    void setDesc(const QString &desc);

    QString icon() const;
    void setIcon(const QString &icon);

private:
    class Private;
    friend class Private;
    Private *d;
};

class WeatherDetail::Private
{
public:
    Private(){

    }

    QString desc;
    QString icon;
};

class WeatherInfo
{
public:
    WeatherInfo();
    ~WeatherInfo();

    QString cityName() const;
    void setCityName(const QString &cityName);

    quint32 id() const;
    void setId(quint32 id);

    QDateTime datetime() const;
    void setDateTime(const QDateTime &dateTime);

    float temperature() const;
    void setTemperature(float temperature);

    float humidity() const;
    void setHumidity(float humidify);

    float pressure() const;
    void setPressure(float pressure);

    QList<WeatherDetail *> details() const;
    void setDetails(const QList<WeatherDetail *> details);

private:
    class Private;
    friend class Private;
    Private *d;
};

class WeatherInfo::Private
{
public:
    Private(){}
    QString cityName;
    quint32 id;
    QDateTime dateTime;
    float temperature;
    float humidify;
    float pressure;
    QList<WeatherDetail *> details;
};

QDebug operator <<(QDebug dbg, const WeatherDetail &w);
QDebug operator <<(QDebug dbg, const WeatherInfo &w);

#endif // WEATHERDETAIL_H

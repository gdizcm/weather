#include "global.h"

#include "weatherdetail.h"

WeatherDetail::WeatherDetail():
    d(new WeatherDetail::Private)
{

}

WeatherDetail::~WeatherDetail()
{

}

QString WeatherDetail::desc() const
{
    return this->d->desc;
}

void WeatherDetail::setDesc(const QString &desc)
{
    this->d->desc = desc;
}

QString WeatherDetail::icon() const
{
    return this->d->icon;
}

void WeatherDetail::setIcon(const QString &icon)
{
    this->d->icon = icon;
}

WeatherInfo::WeatherInfo():d(new WeatherInfo::Private)
{

}

WeatherInfo::~WeatherInfo()
{

}

QString WeatherInfo::cityName() const
{
    return this->d->cityName;
}

void WeatherInfo::setCityName(const QString &cityName)
{
    this->d->cityName = cityName;
}

quint32 WeatherInfo::id() const
{
    return this->d->id;
}

void WeatherInfo::setId(quint32 id)
{
    this->d->id = id;
}

QDateTime WeatherInfo::datetime() const
{
    return this->d->dateTime;
}

void WeatherInfo::setDateTime(const QDateTime &dateTime)
{
    this->d->dateTime = dateTime;
}

float WeatherInfo::temperature() const
{
    return this->d->temperature;
}

void WeatherInfo::setTemperature(float temperature)
{
    this->d->temperature = temperature;
}

float WeatherInfo::humidity() const
{
    return this->d->humidify;
}

void WeatherInfo::setHumidity(float humidify)
{
    this->d->humidify = humidify;
}

float WeatherInfo::pressure() const
{
    return this->d->pressure;
}

void WeatherInfo::setPressure(float pressure)
{
    this->d->pressure = pressure;
}

QList<WeatherDetail *> WeatherInfo::details() const
{
    return this->d->details;
}

void WeatherInfo::setDetails(const QList<WeatherDetail *> details)
{
    this->d->details = details;
}

QDebug operator <<(QDebug dbg, const WeatherDetail &w)
{
    dbg.nospace() << "("
                  << "Description: " << w.desc() << "; "
                  << "Icon: " << w.icon()
                  << ")";
    return dbg.space();
}

QDebug operator <<(QDebug dbg, const WeatherInfo &w)
{
    dbg.nospace() << "("
                  << "id: " << w.id() << "; "
                  << "City name: " << w.cityName() << "; "
                  << "Date time: " << w.datetime().toString(Qt::DefaultLocaleLongDate) << ": " << endl
                  << "Temperature: " << w.temperature() << ", "
                  << "Pressure: " << w.pressure() << ", "
                  << "Humidity: " << w.humidity() << endl
                  << "Details: [";
    foreach (WeatherDetail *detail, w.details()) {
        dbg.nospace() << "( Description: " << detail->desc() << ", "
                      << "Icon: " << detail->icon() << "), ";
    }
    dbg.nospace() << "] )";
    return dbg.space();
}

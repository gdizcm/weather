#include "global.h"

#include "mainwindow.h"
#include <QWidget>
#include <QDateTime>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QNetworkReply>
#include "weatherdetail.h"
#include <QMessageBox>
#include <QNetworkProxy>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      d(new MainWindow::Private(this))
{
    QComboBox *cityList = new QComboBox(this);
    cityList->addItem(tr("Beijing"), QStringLiteral("Beijing,cn"));
    cityList->addItem(tr("Shanghai"), QStringLiteral("Shanghai,cn"));
    cityList->addItem(tr("Dalian"), QStringLiteral("Dalian,cn"));
    cityList->addItem(tr("Qingdao"), QStringLiteral("Qingdao,cn"));
    cityList->addItem(tr("Wafangdian"), QStringLiteral("Wafangdian,cn"));

    QLabel *cityLabel = new QLabel(tr("City:"), this);
    cityLabel->setFrameStyle(QFrame::Box);
    QPushButton *refreshButton = new QPushButton(tr("Refresh"), this);
    QHBoxLayout *cityListLayout = new QHBoxLayout;
    cityListLayout->setDirection(QBoxLayout::LeftToRight);
    cityListLayout->addWidget(cityLabel);
    cityListLayout->addWidget(cityList);
    cityListLayout->addWidget(refreshButton);

    QVBoxLayout *weatherLayout = new QVBoxLayout;
    weatherLayout->setDirection(QBoxLayout::TopToBottom);
    QLabel *cityNameLabel = new QLabel(this);
    cityNameLabel->setFrameStyle(QFrame::Box);
    weatherLayout->addWidget(cityNameLabel);
    QLabel *dateTimeLabel = new QLabel(this);
    dateTimeLabel->setFrameStyle(QFrame::Box);
    weatherLayout->addWidget(dateTimeLabel);

    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addLayout(cityListLayout);
    mainLayout->addLayout(weatherLayout);
    setCentralWidget(mainWidget);
    resize(320, 120);
    setWindowTitle(tr("Weather"));

    QHBoxLayout *weatherDetailLayout = new QHBoxLayout;
    weatherDetailLayout->setDirection(QBoxLayout::LeftToRight);
    QLabel *labelweather = new QLabel(this);
    labelweather->setFrameStyle(QFrame::Box);
    weatherDetailLayout->addWidget(labelweather);
    QLabel *labelIcon = new QLabel(this);
    labelIcon->setFrameStyle(QFrame::Box);
    weatherDetailLayout->addWidget(labelIcon);
    QLabel *labeltemp = new QLabel(this);
    labeltemp->setFrameStyle(QFrame::Box);
    weatherDetailLayout->addWidget(labeltemp);
    weatherLayout->addLayout(weatherDetailLayout);




    connect(d->netWorker, &NetWorker::finished, [=](QNetworkReply *reply) {
        RemoteRequest request = d->replyMap.value(reply);
        switch (request) {
        case FetchWeatherInfo:
        {
            QJsonParseError error;
            QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
            //qDebug()<<jsonDocument.toJson(QJsonDocument::Indented);
            if (error.error == QJsonParseError::NoError) {
                if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
                    QVariantMap data = jsonDocument.toVariant().toMap();
                    WeatherInfo weather;
                    weather.setCityName(data[QLatin1String("name")].toString());
                    QDateTime dateTime;
                    dateTime.setTime_t(data[QLatin1String("dt")].toLongLong());
                    weather.setDateTime(dateTime);
                    QVariantMap main = data[QLatin1String("main")].toMap();
                    weather.setTemperature(main[QLatin1String("temp")].toFloat());
                    weather.setPressure(main[QLatin1String("pressure")].toFloat());
                    weather.setHumidity(main[QLatin1String("humidity")].toFloat());
                    QVariantList detailList = data[QLatin1String("weather")].toList();

                    QVariantMap sys = data[QLatin1String("sys")].toMap();
                    QDateTime sunrise;
                    sunrise.setTime_t(sys[QLatin1String("sunrise")].toLongLong());
                    qDebug()<< sunrise.toString(Qt::DefaultLocaleLongDate);
                    QDateTime sunset;
                    sunset.setTime_t(sys[QLatin1String("sunset")].toLongLong());
                    qDebug()<< sunset.toString(Qt::DefaultLocaleLongDate);

                    labeltemp->setText(QString("%1").arg(weather.temperature()));

                    QList<WeatherDetail *> details;

                    foreach (QVariant w, detailList) {
                        QVariantMap wm = w.toMap();
                        WeatherDetail *detail = new WeatherDetail;
                        detail->setDesc(wm[QLatin1String("description")].toString());
                        detail->setIcon(wm[QLatin1String("icon")].toString());
                        details.append(detail);


                        //QLabel *label = (QLabel *)weatherLayout->itemAt(2)->layout()->itemAt(0)->widget();
                        labelweather->setText(detail->desc());
                        //weatherDetailLayout->addWidget(label);

                        d->fetchIcon(detail->icon());
                    }

                    weather.setDetails(details);

                    cityNameLabel->setText(weather.cityName());
                    dateTimeLabel->setText(tr("Update Time:")+weather.datetime().toString(Qt::DefaultLocaleLongDate));
                }
            }
            else {
                QMessageBox::critical(this, tr("Error"), error.errorString());
            }
            break;
        }
        case FetchWeatherIcon:
        {
            //QHBoxLayout *weatherDetailLayout = (QHBoxLayout *)weatherLayout->itemAt(2)->layout();
            //QLabel *iconLabel = (QLabel *)weatherDetailLayout->itemAt(1)->widget();
            QPixmap pixmap;
            pixmap.loadFromData(reply->readAll());
            //iconLabel->setPixmap(pixmap);
            labelIcon->setPixmap(pixmap);

            break;
        }
        }
        reply->deleteLater();
    });
    connect(refreshButton, &QPushButton::clicked, [=]() {
        d->fetchWeather(cityList->itemData(cityList->currentIndex()).toString());
    });
}

MainWindow::~MainWindow()
{

}

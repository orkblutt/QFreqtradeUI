#include "restclient.h"
#include <QDebug>
#include <QUrlQuery>

#define FT_RESTAPI_ROOT "/api/v1/"
#define FT_RESTAPI_BALANCE "balance"
#define FT_RESTAPI_PERFORMANCE "performance"
#define FT_RESTAPI_PROFIT "profit"
#define FT_RESTAPI_STATUS "status"
#define FT_RESTAPI_TRADES_HISTORY "trades"
#define FT_RESTAPI_START    "start"
#define FT_RESTAPI_STOP     "stop"
#define FT_RESTAPI_STOPBUY  "stopbuy"
#define FT_RESTAPI_RELOADCONF "reload_conf"
#define FT_RESTAPI_FORCE_SELL "forcesell"
#define FT_RESTAPI_FORCE_BUY "forcebuy"
#define FT_RESTAPI_SHOW_CONFIG "show_config"

restClient::restClient(QObject *parent) : QObject(parent)
{
    Q_UNUSED(parent);

    _netMngrBalance = new QNetworkAccessManager(this);
    _netMngrPerformance = new QNetworkAccessManager(this);
    _netMngrStatus = new QNetworkAccessManager(this);
    _netMngrProfit  = new QNetworkAccessManager(this);
    _netMngrTradeHistory  = new QNetworkAccessManager(this);
    _netMngrStart = new QNetworkAccessManager(this);
    _netMngrStop = new QNetworkAccessManager(this);
    _netMngrStopBuy = new QNetworkAccessManager(this);
    _netMngrReloadConf = new QNetworkAccessManager(this);
    _netMngrForceSell = new QNetworkAccessManager(this);
    _netMngrForceBuy = new QNetworkAccessManager(this);
    _netMngrShowConfig = new QNetworkAccessManager(this);

    connect(_netMngrBalance,  &QNetworkAccessManager::finished,
            this, &restClient::replyBalance, Qt::DirectConnection);
    connect(_netMngrPerformance,  &QNetworkAccessManager::finished,
            this, &restClient::replyPerformance, Qt::DirectConnection);
    connect(_netMngrStatus,  &QNetworkAccessManager::finished,
            this, &restClient::replyStatus, Qt::DirectConnection);
    connect(_netMngrProfit,  &QNetworkAccessManager::finished,
            this, &restClient::replyProfit, Qt::DirectConnection);
    connect(_netMngrTradeHistory,  &QNetworkAccessManager::finished,
            this, &restClient::replyTradesHistory, Qt::DirectConnection);
    connect(_netMngrStart,  &QNetworkAccessManager::finished,
            this, &restClient::replyStart, Qt::DirectConnection);
    connect(_netMngrStop,  &QNetworkAccessManager::finished,
            this, &restClient::replyStop, Qt::DirectConnection);
    connect(_netMngrStopBuy,  &QNetworkAccessManager::finished,
            this, &restClient::replyStopBuy, Qt::DirectConnection);
    connect(_netMngrReloadConf,  &QNetworkAccessManager::finished,
            this, &restClient::replyReloadConf, Qt::DirectConnection);
    connect(_netMngrForceSell,  &QNetworkAccessManager::finished,
            this, &restClient::replyForceSell, Qt::DirectConnection);
    connect(_netMngrForceBuy,  &QNetworkAccessManager::finished,
            this, &restClient::replyForceBuy, Qt::DirectConnection);
    connect(_netMngrShowConfig,  &QNetworkAccessManager::finished,
            this, &restClient::replyShowConfig, Qt::DirectConnection);
}

void restClient::getBalance()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_BALANCE));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrBalance->get(netReq);
}

void restClient::getPerformance()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_PERFORMANCE));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrPerformance->get(netReq);
}

void restClient::getStatus()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_STATUS));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrStatus->get(netReq);
}

void restClient::getProfit()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_PROFIT));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrProfit->get(netReq);
}

void restClient::getHistory()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_TRADES_HISTORY));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrTradeHistory->get(netReq);
}

void restClient::postStart()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_START));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrStart->post(netReq, QByteArray());
}

void restClient::postStop()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_STOP));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrStop->post(netReq, QByteArray());
}

void restClient::postStopBuy()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_STOPBUY));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrStopBuy->post(netReq, QByteArray());
}

void restClient::postReloadConf()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_RELOADCONF));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrReloadConf->post(netReq, QByteArray());
}

void restClient::postForceSell(const int id)
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_FORCE_SELL));
    QUrlQuery qquery;
    qquery.addQueryItem("symbol", QString::number(id));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrForceSell->post(netReq, qquery.toString(QUrl::FullyEncoded).toUtf8());
}

void restClient::postForceSellAll()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_FORCE_SELL));
    QUrlQuery qquery;
    qquery.addQueryItem("symbol", "all");
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrForceSell->post(netReq, qquery.toString(QUrl::FullyEncoded).toUtf8());
}

void restClient::postForceBuy(const QString &pair, double amount)
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_FORCE_BUY));
    QByteArray jsonString = QString("{\"pair\":\"%1\",\"price\": %2}").arg(pair).arg(amount).toUtf8();
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrForceBuy->post(netReq, jsonString);
}

void restClient::getShowConfig()
{
    QUrl url(QString("%1%2%3").arg(_url).arg(FT_RESTAPI_ROOT).arg(FT_RESTAPI_SHOW_CONFIG));
    QNetworkRequest netReq;
    netReq.setUrl(url);
    netReq.setRawHeader("Authorization", _authHelper);
    _netMngrShowConfig->get(netReq);

}

void restClient::replyBalance(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        emit balanceSignal(QJsonDocument::fromJson(data));
    }
}

void restClient::replyPerformance(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        emit performanceSignal(QJsonDocument::fromJson(data));
    }
}

void restClient::replyStatus(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        emit statusSignal(QJsonDocument::fromJson(data));
    }
}

void restClient::replyProfit(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        emit profitSignal(QJsonDocument::fromJson(data));
    }
}

void restClient::replyTradesHistory(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        emit historySignal(QJsonDocument::fromJson(data));
    }
}

void restClient::replyStart(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        qDebug() << data;
    }
}

void restClient::replyStop(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        qDebug() << data;
    }
}

void restClient::replyStopBuy(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        qDebug() << data;
    }
}

void restClient::replyReloadConf(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        qDebug() << data;
    }
}

void restClient::replyForceSell(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        qDebug() << data;
    }
}

void restClient::replyForceBuy(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {
        qDebug() << data;
    }
}

void restClient::replyShowConfig(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    if(!data.isEmpty())
    {

        emit showConfigSignal(QJsonDocument::fromJson(data).toJson(QJsonDocument::Indented));
    }
}

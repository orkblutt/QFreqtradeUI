#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class restClient : public QObject
{
    Q_OBJECT
public:
    explicit restClient(QObject *parent = nullptr);

    void getBalance();
    void getPerformance();
    void getStatus();
    void getProfit();
    void getHistory();

    void postStart();
    void postStop();
    void postStopBuy();
    void postReloadConf();
    void postForceSell(const int id);
    void postForceSellAll();
    void postForceBuy(const QString& pair, double amount);
    void getShowConfig();


    void setURLPort(const QString& url, const int& port){_url =QString("http://%1:%2").arg(url).arg(port);};
    void setCredentials(const QString& name, const QString& password)
    {
        _authHelper = "Basic " + QByteArray(QString("%1:%2").arg(name).arg(password).toStdString().c_str()).toBase64();
    };


private:

    QNetworkAccessManager* _netMngrBalance;
    QNetworkAccessManager* _netMngrPerformance;
    QNetworkAccessManager* _netMngrStatus;
    QNetworkAccessManager* _netMngrProfit;
    QNetworkAccessManager* _netMngrTradeHistory;
    QNetworkAccessManager* _netMngrStart;
    QNetworkAccessManager* _netMngrStop;
    QNetworkAccessManager* _netMngrStopBuy;
    QNetworkAccessManager* _netMngrReloadConf;
    QNetworkAccessManager* _netMngrForceSell;
    QNetworkAccessManager* _netMngrForceBuy;
    QNetworkAccessManager* _netMngrShowConfig;

    QString _url;
    QByteArray _authHelper;


public slots:

    void replyBalance(QNetworkReply* reply);
    void replyPerformance(QNetworkReply* reply);
    void replyStatus(QNetworkReply* reply);
    void replyProfit(QNetworkReply* reply);
    void replyTradesHistory(QNetworkReply* reply);
    void replyStart(QNetworkReply* reply);
    void replyStop(QNetworkReply* reply);
    void replyStopBuy(QNetworkReply* reply);
    void replyReloadConf(QNetworkReply* reply);
    void replyForceSell(QNetworkReply* reply);
    void replyForceBuy(QNetworkReply* reply);
    void replyShowConfig(QNetworkReply* reply);

signals:

    void balanceSignal(QJsonDocument);
    void performanceSignal(QJsonDocument);
    void statusSignal(QJsonDocument);
    void profitSignal(QJsonDocument);
    void historySignal(QJsonDocument);
    void showConfigSignal(const QString);

};

#endif // RESTCLIENT_H

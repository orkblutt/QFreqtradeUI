#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include "qjsontablemodel.h"
#include "restclient.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    restClient _client;
    QJsonTableModel* _balanceTableModel;
    QJsonTableModel* _perfTableModel;
    QJsonTableModel* _statusTableModel;
    QJsonTableModel* _historyTableModel;
    QTimer  _refreshTimer;
    QSettings* _settings;

    bool _oneClickCommand = false;


    bool missClickProtection();

public slots:

    void onBalance(QJsonDocument jDoc);
    void onPerformance(QJsonDocument jDoc);
    void onStatus(QJsonDocument jDoc);
    void onProfit(QJsonDocument jDoc);
    void onHistory(QJsonDocument jDoc);

    void onShowConfig(const QString conf);

    void onRefresh();

private slots:
    void on_pushButtonOptions_pressed();
    void on_pushButtonStart_pressed();
    void on_pushButtonStop_pressed();
    void on_pushButtonStopbuy_pressed();
    void on_pushButtonReloadconf_pressed();
    void on_pushButtonForcesell_pressed();
    void on_pushButtonForceSellAll_pressed();
    void on_pushButtonForcebuy_pressed();
    void on_pushButtonShowConfig_pressed();
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSortFilterProxyModel>
#include <QThread>
#include <QDir>
#include <QMessageBox>
#include "optionsdialog.h"
#include "buydialog.h"
#include "confviewerdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _settings = new QSettings(QString(QDir::currentPath() + QDir::separator() + "freqtradeui.ini"), QSettings::IniFormat);
    _lastProfit = _settings->value("profit", 0.0).toDouble();

    QJsonTableModel::Header headerBalance;
    headerBalance.push_back( QJsonTableModel::Heading( { {"title","Currency"},   {"index","currency"} }) );
    headerBalance.push_back( QJsonTableModel::Heading( { {"title","Balance"},    {"index","balance"} }) );
    headerBalance.push_back( QJsonTableModel::Heading( { {"title","Estimated stake"},  {"index","est_stake"} }) );
    headerBalance.push_back( QJsonTableModel::Heading( { {"title","Base currency"},  {"index","stake"} }) );

    QSortFilterProxyModel* proxyBalanceModel = new QSortFilterProxyModel(this);
    _balanceTableModel = new QJsonTableModel(headerBalance, this);
    proxyBalanceModel->setSourceModel(_balanceTableModel);
    ui->tableViewBalance->setModel(proxyBalanceModel);
    ui->tableViewBalance->setSortingEnabled(true);
    ui->tableViewBalance->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonTableModel::Header headerPerf;
    headerPerf.push_back( QJsonTableModel::Heading( { {"title","Pair"},   {"index","pair"} }) );
    headerPerf.push_back( QJsonTableModel::Heading( { {"title","Profit"},    {"index","profit"} }) );
    headerPerf.push_back( QJsonTableModel::Heading( { {"title","Trades Count"},  {"index","count"} }) );

    QSortFilterProxyModel* proxyPerfModel = new QSortFilterProxyModel(this);
    _perfTableModel = new QJsonTableModel(headerPerf, this);
    proxyPerfModel->setSourceModel(_perfTableModel);
    ui->tableViewPerf->setModel(proxyPerfModel);
    ui->tableViewPerf->setSortingEnabled(true);
    ui->tableViewPerf->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonTableModel::Header headerStatus;
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","ID"},   {"index","trade_id"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Pair"},  {"index","pair"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Amount"},   {"index","amount"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Open rate"},    {"index","open_rate"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Stake amount"},   {"index","stake_amount"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Base currency"},    {"index","base_currency"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Profit"},  {"index","current_profit"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Current rate"},   {"index","current_rate"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Stop loss"},    {"index","stop_loss"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","initial_stop_loss"},    {"index","initial_stop_loss"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","initial_stop_loss_pct"},  {"index","initial_stop_loss_pct"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","stop_loss_pct"},  {"index","stop_loss_pct"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Open date"},  {"index","open_date"} }) );
    headerStatus.push_back( QJsonTableModel::Heading( { {"title","Duration"},   {"index","open_date_hum"} }) );

    QSortFilterProxyModel* proxyStatusModel = new QSortFilterProxyModel(this);
    _statusTableModel = new QJsonTableModel(headerStatus, this);
    proxyStatusModel->setSourceModel(_statusTableModel);
    ui->tableViewStatus->setModel(proxyStatusModel);
    ui->tableViewStatus->setSortingEnabled(true);
    ui->tableViewStatus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonTableModel::Header headerHistory;
    headerHistory.push_back( QJsonTableModel::Heading({{"title","ID"},   {"index","trade_id"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Pair"},  {"index","pair"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Amount"},   {"index","amount"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Stake amount"},   {"index","stake_amount"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Close profit"},   {"index","close_profit"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Sell reason"},   {"index","sell_reason"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Open rate"},    {"index","open_rate"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Open rate requested"},    {"index","open_rate_requested"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Close rate"},   {"index","close_rate"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Close rate requested"},   {"index","close_rate_requested"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Open date"},  {"index","open_date"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Close date"},   {"index","close_date"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Close date hum"},   {"index","close_date_hum"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Stop loss"},    {"index","stop_loss"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","initial_stop_loss"},    {"index","initial_stop_loss"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","initial_stop_loss_pct"},  {"index","initial_stop_loss_pct"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","stop_loss_pct"},  {"index","stop_loss_pct"} }) );
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Strategy"},  {"index","strategy"}}));
    headerHistory.push_back( QJsonTableModel::Heading({{"title","Ticker interval"},  {"index","ticker_interval"}}));

    QSortFilterProxyModel* proxyHistoryModel = new QSortFilterProxyModel(this);
    _historyTableModel = new QJsonTableModel(headerHistory, this);
    proxyHistoryModel->setSourceModel(_historyTableModel);
    ui->tableViewTradesHistory->setModel(proxyHistoryModel);
    ui->tableViewTradesHistory->setSortingEnabled(true);
    ui->tableViewTradesHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    connect(&_client, SIGNAL(balanceSignal(QJsonDocument)), this, SLOT(onBalance(QJsonDocument)));
    connect(&_client, SIGNAL(performanceSignal(QJsonDocument)), this, SLOT(onPerformance(QJsonDocument)));
    connect(&_client, SIGNAL(statusSignal(QJsonDocument)), this, SLOT(onStatus(QJsonDocument)));
    connect(&_client, SIGNAL(profitSignal(QJsonDocument)), this, SLOT(onProfit(QJsonDocument)));
    connect(&_client, SIGNAL(historySignal(QJsonDocument)), this, SLOT(onHistory(QJsonDocument)));

    connect(&_client, SIGNAL(showConfigSignal(const QString)), this, SLOT(onShowConfig(const QString)));


    _client.setURLPort(_settings->value("address").toString(), _settings->value("port").toInt());
    _client.setCredentials(_settings->value("username").toString(), _settings->value("password").toString());

    _oneClickCommand = _settings->value("one_click").toBool();

    connect(&_refreshTimer, SIGNAL(timeout()), this, SLOT(onRefresh()));
    _refreshTimer.start(_settings->value("refresh_interval", 60).toInt() * 1000);
    onRefresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::missClickProtection()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure to want to continue ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return (msgBox.exec() == QMessageBox::Yes);
}


void MainWindow::onBalance(QJsonDocument jDoc)
{
    QJsonObject obj = jDoc.object();
    QJsonDocument jdo(obj["currencies"].toArray());
    _balanceTableModel->setJson((jdo));
    ui->label_balanceValue->setText(QString("%1 %2").arg(QString::number(obj["total"].toDouble())).arg(obj["stake"].toString()));
}

void MainWindow::onPerformance(QJsonDocument jDoc)
{
    _perfTableModel->setJson(jDoc);
}

void MainWindow::onStatus(QJsonDocument jDoc)
{
    _statusTableModel->setJson(jDoc);
}

void MainWindow::onProfit(QJsonDocument jDoc)
{
    QJsonObject obj = jDoc.object();
    double currentProfit = obj["profit_closed_percent"].toDouble();
    ui->label_bestPair->setText(QString("Best pair: %1 %2").arg(obj["best_pair"].toString()).arg(obj["best_rate"].toDouble()));
    ui->label_profit->setText(QString("Profit: %1%").arg(currentProfit));
    ui->label_tradeCount->setText(QString("Trades count: %1").arg(obj["trade_count"].toInt()));

    if(currentProfit != _lastProfit)
    {
        ui->label_profit->setPixmap(QPixmap(currentProfit > _lastProfit ? ":/images/arrow_up.png" : ":/images/arrow_down.png"));
        _lastProfit = currentProfit;
        _settings->setValue("profit", currentProfit);
    }
}

void MainWindow::onHistory(QJsonDocument jDoc)
{
    QJsonObject obj = jDoc.object();
    QJsonDocument jdo(obj["trades"].toArray());
    _historyTableModel->setJson((jdo));
}

void MainWindow::onShowConfig(const QString conf)
{
    ConfViewerDialog* dlg = new ConfViewerDialog(conf);
    dlg->exec();
    delete dlg;

}

void MainWindow::onRefresh()
{
    _client.getBalance();
    _client.getStatus();
    _client.getPerformance();
    _client.getProfit();
    _client.getHistory();
}


void MainWindow::on_pushButtonOptions_pressed()
{
    OptionsDialog* opt = new OptionsDialog(_settings->value("address").toString()
                                           , _settings->value("port").toInt()
                                           , _settings->value("username").toString()
                                           , _settings->value("password").toString()
                                           , _settings->value("remember").toBool()
                                           , _settings->value("refresh_interval").toInt()
                                           , _settings->value("one_click").toBool()
                                           , this );
    if(opt->exec() == 1)
    {
        QString address, username, password;
        int port, interval;
        bool remember, oneclick;

        opt->getOptions(address, port, username, password, remember, interval, oneclick);

        _client.setURLPort(address, port);
        _client.setCredentials(username, password);

        _oneClickCommand = oneclick;

        if(!remember)
        {
            address = "";
            port = 0;
            username = "";
            password = "";
            remember = false;
            interval = 20;
            oneclick = false;
        }

        _settings->setValue("address", address);
        _settings->setValue("port", port);
        _settings->setValue("username", username);
        _settings->setValue("password", password);
        _settings->setValue("remember", remember);
        _settings->setValue("refresh_interval", interval);
        _settings->setValue("one_click", oneclick);

        _refreshTimer.stop();
        _refreshTimer.start(interval * 1000);
    }
}

void MainWindow::on_pushButtonStart_pressed()
{
    if(!_oneClickCommand && !missClickProtection())
        return;
    _client.postStart();
}

void MainWindow::on_pushButtonStop_pressed()
{
    if(!_oneClickCommand && !missClickProtection())
        return;
    _client.postStop();
}

void MainWindow::on_pushButtonStopbuy_pressed()
{
    if(!_oneClickCommand && !missClickProtection())
        return;
    _client.postStopBuy();
}

void MainWindow::on_pushButtonReloadconf_pressed()
{
    if(!_oneClickCommand && !missClickProtection())
        return;
    _client.postReloadConf();
}

void MainWindow::on_pushButtonForcesell_pressed()
{
    if(!_oneClickCommand && !missClickProtection())
        return;

    QModelIndex index = ui->tableViewStatus->currentIndex().siblingAtColumn(0);
    int tradeId = index.data(Qt::DisplayRole).toInt();
    if(tradeId != 0)
        _client.postForceSell(tradeId);
}

void MainWindow::on_pushButtonForceSellAll_pressed()
{
}

void MainWindow::on_pushButtonForcebuy_pressed()
{
   BuyDialog dlg;
   if(dlg.exec() == 1)
   {
       if(!_oneClickCommand && !missClickProtection())
           return;

       _client.postForceBuy(dlg.getPair(), dlg.getRate());
   }
}

void MainWindow::on_pushButtonShowConfig_pressed()
{
    _client.getShowConfig();
}

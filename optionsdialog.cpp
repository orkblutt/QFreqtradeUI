#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(const QString& address, const int& port, const QString& username, const QString& password, const bool& remember, const int& interval, const bool& oneclick, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    ui->lineEditAddr->setText(address);
    ui->lineEditPort->setText(QString::number(port));
    ui->lineEditUsername->setText(username);
    ui->lineEditPassword->setText(password);
    ui->checkBoxRemember->setChecked(remember);
    ui->lineEditRefreshInterval->setText(QString::number(interval));
    ui->checkBoxOneClick->setChecked(oneclick);

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::getOptions(QString &address, int &port, QString &username, QString &password, bool& remember, int& interval, bool& oneclick)
{
    address = ui->lineEditAddr->text();
    port = ui->lineEditPort->text().toInt();
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();
    remember = ui->checkBoxRemember->isChecked();
    interval = ui->lineEditRefreshInterval->text().toInt();
    oneclick = ui->checkBoxOneClick->isChecked();

}


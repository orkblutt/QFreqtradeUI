#include "buydialog.h"
#include "ui_buydialog.h"

BuyDialog::BuyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyDialog)
{
    ui->setupUi(this);
}

BuyDialog::~BuyDialog()
{
    delete ui;
}

QString BuyDialog::getPair()
{
    return ui->lineEditPair->text();
}

double BuyDialog::getRate()
{
    return ui->lineEditRate->text().toDouble();
}
